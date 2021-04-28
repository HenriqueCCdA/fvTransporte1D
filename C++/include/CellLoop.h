#ifndef CELLLOOP_H
#define CELLLOOP_H

#include"Mesh.h"
#include"Solver.h"
#include"IntTemp.h"


enum cc { cce = 1, ccd = 2 };


/******************************************************************************
 *@class  CellLoop
 ******************************************************************************
 *@brief   A Classe loop nas c�lulas.
 *@details A Classe loop nas c�lulas e uma classe generica.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
class CellLoop {

  public:

    virtual void montaSistema(void)=0;

};

/****************************************************************************** 
 *@class  CellHeatLoop
 ******************************************************************************
 *@brief   A Classe do loop nas c�lulas do problema de Calor.
 *@details A Classe do loop nas c�lulas do problema de Calor.  Esta classe  <!--
 *-->      e filha da Classe CellLoop. Esta classe trabalha com com os      <!--
 * -->     objetos mesh, solver e intTemp 
  ******************************************************************************
 *@date      2021-2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/

class CellHeatLoop: public CellLoop{

  private:
    Solver *solver;   /**< solver para o sistema de equa��es*/
    Mesh *mesh;       /**< malha do problema*/
    IntTemp *intTemp; /**< Integra��o numerica temporal*/ 

  public:

    /***************************************************************************
     *@brief Contrutor
     *@details Este construtor recebe um ponteiro para solver, mesh e intTemp. <!--
     **************************************************************************
     *@date      19/04/2021 - 25/04/2021
     *@author    Henrique C. C. de Andrade
     ***************************************************************************/
    CellHeatLoop(Solver *solver, Mesh *mesh, IntTemp *intTemp) {
      this->solver = solver;
      this->mesh = mesh;
      this->intTemp = intTemp;
    }

    void montaSistema(void) override;

};
#endif
