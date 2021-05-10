#ifndef FIELDS_H
#define FIELDS_H

#include"GerenciadoDeMemoria.h"

/*******************************************************************************
 *@class Field   
 *******************************************************************************
 *@brief     Classe base dos campos de variaveis               
 *@details   Classe base dos campos de variaveis      
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Field {

  private:
    int n;    /**< Número de posições*/
    int ndf;  /**< Número de graus de liberdade*/
    int ndm;  /**< Dimensão do problema (1 , 2, 3)*/

  public:

    void set_n(int n){ this->n = n;};
    void set_ndf(int n) { this->ndf = n;};
    void set_ndm(int n) { this->ndm = n;};
  
    int get_n(void) { return this->n;};
    int get_ndf(void) { return  this->ndf;};
    int get_ndm(void) { return this->ndm;};

    virtual void alloc(void) = 0;

    virtual ~Field(){
      #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << std::endl;
      #endif // DEBUG  
    }

};
//******************************************************************************
#endif