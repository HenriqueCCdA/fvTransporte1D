#include"../include/EpdSolver.h"
#include"../include/RunTimes.h"

/********************************************************************************
*@details Procedimento principal da solução da EDP. Neste método e executado     <!--
*-->      o fluxo principal de solução.
*********************************************************************************
*@date      19/04/2021 - 05/05/2021
*@author    Henrique C. C. de Andrade
*********************************************************************************/
template <class TField> void EpdSolver<TField>::solver(void){

  int nStep = intTemp->get_nStep();
  double *uCell  = mesh->get_cells().get_fields().get_u(timeLevel::nPlusOne);

  // ...
  times.init_timer();
  this->writer->write();
  times.updateResTimer();
  // ............................................................................

  //
  this->mesh->nodalInterpol();
  // ............................................................................

  // ... calculo do gradiente e fluxo
  this->cellLoop->gradients();
  this->cellLoop->flux();
  // ............................................................................

  // ...
  times.init_timer();
  this->writer->write();
  times.updateResTimer();
  // ............................................................................

  cout << "Running ..." << endl;

  for (int j = 0; j < nStep; j++) {

    // ...
    this->intTemp->updateTime();
    this->intTemp->display();
    // ........................................................................

    for(int j = 0; j < 10; j++){

      // ...
      this->mesh->get_cells().updateProp();
      // ......................................................................

      // ...
      times.init_timer();
      this->cellLoop->montaSistema();
      times.updateSistTimer();
      // ......................................................................

      // ... checat convergencia
      if(this->convergence(j, true)) break;
      // ......................................................................

      //... solver
      times.init_timer();
      uCell = this->solverEq->solver(uCell);
      times.updateSolverTimer();
      //.......................................................................  

    }
    // ........................................................................

    // ... calculo do gradiente e fluxo
    this->cellLoop->gradients();
    this->cellLoop->flux();
    // ............................................................................
    
    // ... 
    this->mesh->nodalInterpol();
    //...........................................................................

    // ...
    times.init_timer();
    this->writer->write();
    times.updateResTimer();
    // ..........................................................................   

    // ... u(0) -> u(n-1)
    this->updateU();
    // .........................................................................
  }
// ..............................................................................

}
// ******************************************************************************

 /********************************************************************************
 *@details Inicialação dos dado para procedimento de solução da EDP. Esta função  <!--
 *<--      precisa ser chamada antes de método solver
 *********************************************************************************
 *@date      19/04/2021 - 05/05/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField> void EpdSolver<TField>::init(void) {

  int nCells = mesh->get_cells().get_nCells();
  int nNodes = mesh->get_nodes().get_nNodes();
  double u0 = mesh->get_ccci().get_cciValue();
  PropRef propRef = this->mesh->get_propRef();

  // ... iniciando as propriedades
  this->mesh->get_cells().get_prop().init_prop(u0, nCells);

  // ... iniciando as celulas
  this->mesh->get_cells().get_fields().set_u(u0, timeLevel::nZero);
  this->mesh->get_cells().get_fields().set_u(u0, timeLevel::nPlusOne);
  this->mesh->get_cells().get_fields().set_gradU(0.e0);

  // ... iniciando os nodes
  this->mesh->get_nodes().get_fields().set_u(u0);
  this->mesh->get_nodes().get_fields().set_gradU(0.e0);

  //
  this->intTemp->set_iStep(0);
  this->intTemp->set_t(0.0e0);
}
// ******************************************************************************

/********************************************************************************
 *@details Inicialação dos dado para procedimento de solução da EDP. Esta função  <!--
 *<--      precisa ser chamada antes de método solver
 *********************************************************************************
 @param it   - Numero da iteracao do metodo nao linear
 @param plot - Plota o resido da iteracao ( default = false)
 ********************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField>
bool EpdSolver<TField>::convergence(short const it, bool const plot ) {

  int nCells = mesh->get_cells().get_nCells();
  const double* const res = this->mesh->get_cells().get_residuo();
  double modRes = 0.e0;

  for (int i = 0; i < nCells; i++) {
    modRes += res[i]*res[i];
  }
  modRes = sqrt(modRes);

  if (this->firstConverge) {
    this->res0 = modRes;
    this->firstConverge = false;
  }

  double conv = this->res0 * this->tol; 
    
  if(plot)
    std::cout << "It = " <<setw(6) << it
              << " |cellRes| = " 
              << setprecision(7) << scientific <<  modRes
              << std::endl;

  if(modRes < conv)
    return true;
  else
    return false;

}
// ******************************************************************************

/********************************************************************************
 *@details Atualiza a solução. Faz u(0) -> u(n+1).
 *********************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField> void EpdSolver<TField>::updateU(void) {

  int nCells = mesh->get_cells().get_nCells();

  double *u0 = this->mesh->get_cells().get_fields().get_u(timeLevel::nZero);
  double *u = this->mesh->get_cells().get_fields().get_u(timeLevel::nPlusOne);

  for(int i = 0; i < nCells; i++)
    u0[i] = u[i];

}
// ******************************************************************************


// ...
template class EpdSolver<FieldDif>;
// ..............................................................................