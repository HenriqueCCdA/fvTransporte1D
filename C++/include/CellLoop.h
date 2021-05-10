#ifndef CELLLOOP_H
#define CELLLOOP_H

#include"Mesh.h"
#include"Solver.h"
#include"IntTemp.h"
#include"FieldDif.h"


enum cc { cce = 1, ccd = 2 };


/******************************************************************************
 *@class  CellLoop
 ******************************************************************************
 *@brief   A Classe loop nas células.
 *@details A Classe loop nas células e uma classe generica.
 ******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
class CellLoop {

  public:

    virtual void montaSistema(void)=0;
    virtual void gradients(void)=0;
    virtual void flux(void)=0;

    virtual ~CellLoop(){
      #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG 
    };

};

/****************************************************************************** 
 *@class  CellHeatLoop
 ******************************************************************************
 *@brief   A Classe do loop nas células do problema de Calor.
 *@details A Classe do loop nas células do problema de Calor.  Esta classe  <!--
 *-->      e filha da Classe CellLoop. Esta classe trabalha com com os      <!--
 * -->     objetos mesh, solver e intTemp 
  ******************************************************************************
 *@date      2021-2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/

class CellHeatLoop: public CellLoop{

  private:
    Solver *solver;   /**< solver para o sistema de equações*/
    Mesh<FieldDif> *mesh;       /**< malha do problema*/
    IntTemp *intTemp; /**< Integração numerica temporal*/ 

    /********************************************************************************
    *@brief Calcula do gradiente na face do contorno.
    ********************************************************************************/
    double boundaryGrad(short const ccType, const double* const aCcValue,
                        double const uP, double const uV,
                        double const coefDif, double gradU0,
                        double const dx, double const dFace,
                        double const dir);


  public:

    /***************************************************************************
     *@brief Contrutor
    /***************************************************************************/
    CellHeatLoop(Solver *solver, Mesh<FieldDif> *mesh, IntTemp *intTemp);

    void montaSistema(void) override;

    void gradients(void) override;   

    void flux(void) override;

    ~CellHeatLoop(){
      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG  
    }

};
#endif
