#include"../include/CellLoop.h"

/***************************************************************************
*@details Este construtor recebe um ponteiro para solver, mesh e intTemp.  
****************************************************************************
*@date      2021 - 2021
*@author    Henrique C. C. de Andrade
***************************************************************************/
CellHeatLoop::CellHeatLoop(Solver *solver, Mesh<FieldDif> *mesh,
                           IntTemp *intTemp) {
  this->solver = solver;
  this->mesh = mesh;
  this->intTemp = intTemp;
  int n;
  // ... campo de variaveis por celula
  n = mesh->get_nCells();
  this->mesh->get_cells().get_fields().set_n(n);
  this->mesh->get_cells().get_fields().set_ndf(1);
  this->mesh->get_cells().get_fields().set_ndm(1);
  this->mesh->get_cells().get_fields().alloc(typeField::cell);
  // ......................................................................

  // ... campo de variaveis por no
  n = mesh->get_nNodes();
  this->mesh->get_nodes().get_fields().set_n(n);
  this->mesh->get_nodes().get_fields().set_ndf(1);
  this->mesh->get_nodes().get_fields().set_ndm(1);
  this->mesh->get_nodes().get_fields().alloc(typeField::node);
  // ......................................................................

}
/********************************************************************************/


/********************************************************************************
 *@brief     Monta o sistema de equações atraves do loop nas celulas.
 *@details   Monta o sistema de equações atraves do loop nas celulas. <!--
 *-->        A estrutura de dados do sistema de equações é atualizado <!--
 *-->        no final do método.
 ********************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ********************************************************************************/
void CellHeatLoop::montaSistema(void){
  // ...
  double aP0, kf, aE, aW;
  // ..
  double *rho = this->mesh->get_cells().get_prop().get_rho()->get_value();
  double *cp = this->mesh->get_cells().get_prop().get_cp();
  double *ceofDif = this->mesh->get_cells().get_prop().get_coefDif()->get_value();
  // ...
  double dt = this->intTemp->get_dt();
  double dx = this->mesh->get_cells().get_dx();
  // ...
  int cceType = this->mesh->get_ccci().get_cceType(),
      ccdType = this->mesh->get_ccci().get_ccdType();
  double *cceValue = this->mesh->get_ccci().get_cceValue(),
         *ccdValue = this->mesh->get_ccci().get_ccdValue();
  double *u0 = this->mesh->get_cells().get_fields().get_u(timeLevel::nZero);
  double *u  = this->mesh->get_cells().get_fields().get_u(timeLevel::nPlusOne);
  double *resCell = this->mesh->get_cells().get_residuo();
  // ... sistema de equacoes
  TriaDiagonal *triaDiagonal = (TriaDiagonal*) this->solver->get_dataStruct();
  double *aU = triaDiagonal->get_u(),
         *aD = triaDiagonal->get_d(),
         *aL = triaDiagonal->get_l(),
          *b = triaDiagonal->get_b();
  //
  Medias md(medias::mediaHarmonica);

  // ...
  int nCells = this->mesh->get_nCells(), n;
  // ..........................................................................

  // ... Lado esquerdo
  kf = md.medias(ceofDif[0], ceofDif[1]);
  this->boundaryCell(aL[0]  , aD[0], aU[0], b[0],
                     rho[0] , cp[0], ceofDif[0] , kf,
                     dx     , dt   , u0[0],  
                     cceType, cceValue, cce);
  // ... residuo
  resCell[0] = b[0] - (aD[0] * u[0] + aU[0] * u[1]);
  // ............................................................................


  // ... Lado direito
  n = nCells - 1;
  kf = md.medias(ceofDif[n], ceofDif[n-1]);
  this->boundaryCell(aL[n]  , aD[n]   , aU[n], b[n],
                     rho[n] , cp[n]   , ceofDif[n] , kf,
                     dx     , dt      , u0[n],
                     ccdType, ccdValue, ccd);
  resCell[n] = b[n] - (aL[n] * u[n-1] + aD[n] * u[n] );
  // ............................................................................
 
  // ... loop nas celulas do interios
  for (int i = 1; i < nCells - 1; i++) {
    aP0 = rho[i] * cp[i] * dx / dt;
    // ... w
    kf = md.medias(ceofDif[i - 1], ceofDif[i]);
    aW = kf / dx;
    // ...
    kf = md.medias(ceofDif[i], ceofDif[i + 1]);
    aE = kf / dx;
    // ...
    aL[i] = -aW;
    aD[i] = aP0 + aW + aE;
    aU[i] = -aE;
    // ...
    b[i] = aP0 * u0[i];    
    // ... residuo
    resCell[i] = b[i] - (aL[i]*u[i-1] + aD[i]*u[i] + aU[i] * u[i + 1]);
  }
  // ..........................................................................

}
//*****************************************************************************

/********************************************************************************
 *@brief     Caculo do gradiente                                      
 *@details   Cacula o gradiente da propriedade U                          
 ********************************************************************************
 *@date      2021 - 2021                    
 *@author    Henrique C. C. de Andrade
 ********************************************************************************/
void CellHeatLoop::gradients(void) {
  
  // ...
  const double* const coefDif = this->mesh->get_cells().get_prop()
                               .get_coefDif()->get_value();
  // ...
  double const dx = this->mesh->get_cells().get_dx();
  // ...
  int const cceType = this->mesh->get_ccci().get_cceType(),
    ccdType = this->mesh->get_ccci().get_ccdType();
  const double* const cceValue = this->mesh->get_ccci().get_cceValue(),
                      *ccdValue = this->mesh->get_ccci().get_ccdValue();
  const double* const u = this->mesh->get_cells()
                         .get_fields().get_u(timeLevel::nPlusOne);
  double* const gradU = this->mesh->get_cells().get_fields().get_gradU();
  // ...
  int nCells = this->mesh->get_nCells();
  // ..........................................................................

  // ... Lado esquerdo
  gradU[0] = this->boundaryGrad(cceType    , cceValue, u[0], u[1]
                                , coefDif[0],gradU[0]
                                , dx        , 0.5e0*dx
                                , -1.0);
  // ... Lado direito
  int n = nCells - 1;
  gradU[n] = this->boundaryGrad(ccdType, ccdValue, u[n], u[n-1]
                          , coefDif[n], gradU[n]
                          , dx        ,-0.5e0*dx
                          , 1.0);
  // ..........................................................................


  // ... loop nas celulas do interios
  for (int i = 1; i < nCells - 1; i++) {
    gradU[i] = 0.5e0*(u[i+1] - u[i-1])/dx;
  }
  // ..........................................................................
}
//*****************************************************************************

/********************************************************************************
 *@brief     Caculo do fluxo     
 *@details   Caculo do flux de u
 ********************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ********************************************************************************/
void CellHeatLoop::flux(void) {

  // ...
  const double* const coefDif = this->mesh->get_cells()
                         .get_prop().get_coefDif()->get_value();
  const double* const u = this->mesh->get_cells()
                               .get_fields().get_u(timeLevel::nPlusOne);
  const double* const gradU = this->mesh->get_cells().get_fields().get_gradU();
  double* const flux = this->mesh->get_cells().get_fields().get_flux();
  // ...
  int nCells = this->mesh->get_nCells();
  // ..........................................................................

  // ... loop nas celulas do interios
  for (int i = 0; i < nCells; i++) {
    flux[i] = -coefDif[i]*gradU[i];
  }
  // ..........................................................................
}
//*****************************************************************************


/********************************************************************************
 *@brief     Função auxiliar para aplicar as condições de contorno.
 *@details   Função auxiliar para aplicar as condições de contorno.
 ********************************************************************************
 *@param   aL      - termo diagonal inverior
 *@param   aD      - termo diagonal principal
 *@param   aU      - termo diagonal superio
 *@param   b       - termo vetor de forcas
 *@param   rho     - massa especifica
 *@param   cp      - calor especifico
 *@param   kP      - coeficiente de difusao da celula central
 *@param   kF      - coeficiente de difusao na face celula
 *@param   h       - coeficiente de calor convectivo
 *@param   dx      - tamanho da celula
 *@param   dt      - passo de tempo
 *@param   u       - valor da solução do passo de tempo anterior
 *@param   ccType  - tipo da condicao de contorno
 *@param   ccValue - parametros da condicao de contorno      
 ********************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
void CellHeatLoop::boundaryCell(double &aL, double &aD, double &aU, double &b
                              , double rho, double cp, double kP, double kf
                              , double dx, double dt, double u
                              , short ccType, double *aCcValue, short c) {

  double aP0, sU, sP, aWorE;
  double ccValue = aCcValue[0];

  aP0 = rho * cp * dx / dt;
  aWorE = kf / dx;
  // ... temperatura prescrita
  if (ccType == typeCc::temp) {
    sU = (2.0e0*kP / dx)*ccValue;
    sP = -2.0e0*kP / dx;
  }
  // ... fluxo prescrito
  else if (ccType == typeCc::flux) {
    sU    = -ccValue;
    sP    = 0.0;
  }
  // ... lei de resfriamento de newton
  else if (ccType == typeCc::hConv) {
    double h = aCcValue[1];
    double tmp = 1.e0 + (h*2.e0*dx)/kP;
    tmp = h/tmp;
    sU = tmp*ccValue;
    sP = -tmp;
  }
  // ............................................................................

  // ... W
  aL = -((c == cce) ? -0.0 : aWorE);
  // ... P
  aD = aP0 + aWorE - sP;
  // ... E
  aU = -((c == ccd) ? -0.0 : aWorE);
  // ...
  b = sU + aP0 * u;
  // ............................................................................
}
/******************************************************************************/


/********************************************************************************
 *@details     Calcula do gradiente na face do contorno.              
 ********************************************************************************
 *@param   ccType  - tipo da condicao de contorno
 *@param   ccValue - parametros da condicao de contorno
 *@param   dx      - tamanho da celula
 *@param   uP      - valor da solução na celula central             
 *@param   uV      - valor da solução na celula vizinha
 *@param   coefDif - coeficiente de difusao da celula central
 *@param   gradU0  - gradiente na celula centra no passo anterior
 *@param   dx      - tamanho da celula
 *@param   dFace   - distancia ate a face
 *@param   dir     - normal extrena (1 ou - 1)
 ********************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
double CellHeatLoop::boundaryGrad(short const ccType  , const double* const aCcValue,
                                   double const uP     , double const uV,
                                   double const coefDif, double gradU0,
                                   double const dx     ,double const dFace,
                                   double const dir){
  double uB=uP, uF;
  double gradU,q, qn;

  if (ccType == typeCc::temp) {
    uB = aCcValue[0];
  }
  else if (ccType == typeCc::flux) {
    qn = aCcValue[0];
    q = aCcValue[0]*dir;
    gradU = -q / coefDif;
    uB = uP - gradU*dFace;
  }
  else if (ccType == typeCc::hConv) {
    double h = aCcValue[1];
    double tA = aCcValue[0];
    double tS;
   
    tS = uP - gradU0*dFace;
    qn = -h * (tA - tS);
    q = qn * dir;
    gradU = -q / coefDif;
    uB = uP - gradU * dFace;
  }
  
  uF = 0.5e0*(uP + uV);
  return dir * (uB - uF) / dx;
}
/******************************************************************************/