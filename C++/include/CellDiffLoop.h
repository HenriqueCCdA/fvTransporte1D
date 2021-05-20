#ifndef CELLDIFFLOOP_H
#define CELLDIFFLOOP_H

#include"Mesh.h"
#include"Solver.h"
#include"IntTemp.h"
#include"FieldDif.h"
#include"Medias.h"
#include"CellLoop.h"

/******************************************************************************
 *@class  CellDiffLoop
 ******************************************************************************
 *@brief   A Classe do loop nas células do problema de Calor.
 *@details A Classe do loop nas células do problema de Calor.  Esta classe  <!--
 *-->      e filha da Classe CellLoop. Esta classe trabalha com com os      <!--
 * -->     objetos mesh, solver e intTemp
  ******************************************************************************
 *@date      2021-2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/

class CellDiffLoop : public CellLoop {

private:
  Solver *solver;   /**< solver para o sistema de equações*/
  Mesh<FieldDif> *mesh; /**< malha do problema*/
  IntTemp *intTemp; /**< Integração numerica temporal*/

  /********************************************************************************
  *@brief Calcula do gradiente na face do contorno.
  ********************************************************************************/
  double boundaryGrad(short const ccType, const double* const aCcValue,
    double const uP, double const uV,
    double const coefDif, double gradU0,
    double const dx, double const dFace,
    double const dir);

  void boundaryCell(double &aL, double &aD, double &aU, double &b
    , double rho, double cp, double kP, double kV
    , double dx, double dt, double u
    , short ccType, double *aCcValue, short c);
public:

  /***************************************************************************
   *@brief Contrutor
  /***************************************************************************/
  CellDiffLoop(Solver *solver, Mesh<FieldDif> *mesh, IntTemp *intTemp);

  void montaSistema(void) override;

  void gradients(void) override;

  void flux(void) override;

  ~CellDiffLoop() {
#ifdef DEBUG
    std::cout << "Destrutor: " << typeid(this).name() << endl;
#endif // DEBUG  
  }

};
#endif