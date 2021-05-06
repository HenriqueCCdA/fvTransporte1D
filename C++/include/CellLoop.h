#ifndef CELLLOOP_H
#define CELLLOOP_H

#include"Mesh.h"
#include"Solver.h"
#include"IntTemp.h"


enum cc { cce = 1, ccd = 2 };


/******************************************************************************
 *@class  CellLoop
 ******************************************************************************
 *@brief   A Classe loop nas células.
 *@details A Classe loop nas células e uma classe generica.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
class CellLoop {

  public:

    virtual void montaSistema(void)=0;

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

  public:

    /***************************************************************************
     *@brief Contrutor
     *@details Este construtor recebe um ponteiro para solver, mesh e intTemp. <!--
     **************************************************************************
     *@date      2021 - 2021
     *@author    Henrique C. C. de Andrade
     ***************************************************************************/
    CellHeatLoop(Solver *solver, Mesh<FieldDif> *mesh, IntTemp *intTemp) {
      this->solver = solver;
      this->mesh = mesh;
      this->intTemp = intTemp;                 
      FieldDif *fd;
      // ... campo de variaveis por celula
      fd = new FieldDif();
      fd->set_n(mesh->get_nCells());
      fd->set_ndf(1);
      fd->set_ndm(1);
      fd->alloc();
      this->mesh->get_cells().set_fields(fd);
      // ......................................................................
      
      // ... campo de variaveis por no
      fd = new FieldDif();
      fd->set_n(mesh->get_nNodes());
      fd->set_ndf(1);
      fd->set_ndm(1);
      fd->alloc();
      this->mesh->get_nodes().set_fields(fd);
      // ......................................................................

    }

    void montaSistema(void) override;

    ~CellHeatLoop(){
      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG  
      delete this->mesh->get_cells().get_fields();
      delete this->mesh->get_nodes().get_fields();
    }


};
#endif
