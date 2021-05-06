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
  double *uCell = mesh->get_cells().get_fields()->get_u();

  // ...
  times.init_timer();
  this->writer->write();
  times.updateResTimer();
  // ............................................................................

  //
  this->mesh->nodalInterpol();
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
    // ..........................................................................

    // ...
    times.init_timer();
    this->cellLoop->montaSistema();
    times.updateSistTimer();
    // ..........................................................................

    //... solver
    times.init_timer();
    uCell = this->solverEq->solver(uCell);
    times.updateSolverTimer();
    //...........................................................................

    // ... 
    this->mesh->nodalInterpol();
    //...........................................................................

    // ...
    times.init_timer();
    this->writer->write();
    times.updateResTimer();
    // ..........................................................................   

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
  this->mesh->get_cells().get_prop().init_prop(propRef, nCells);

  // ... iniciando as celulas
  this->mesh->get_cells().get_fields()->set_u(u0);

  // ... iniciando os nodes
  this->mesh->get_nodes().get_fields()->set_u(u0);

  //
  this->intTemp->set_iStep(0);
  this->intTemp->set_t(0.0e0);
}
// ******************************************************************************

// ...
template class EpdSolver<FieldDif>;
// ..............................................................................