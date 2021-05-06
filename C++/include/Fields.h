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
      std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG  
    }

};
//******************************************************************************

/*******************************************************************************
 *@class Field
 *******************************************************************************
 *@brief     Classe dos campos de variaveis do problema de difusão.
 *@details   Classe dos campos de variaveis do problema de difusão. Os campos   <!--
 *-->        são u e gradU.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class FieldDif : public Field {

  private:
    double *u;    /**< Campo U*/
    double *gradU;/**< Campo gradiente do campo U*/

  public:

    double* get_u(void){ return this->u;};
    double* get_gradU(void) { return this->gradU; };

    void set_u(double const value) {
      for (int i = 0; i < this->get_n(); i++) {
        this->u[i] = value;
      }
    }

    void alloc(void) override{
      int n = this->get_n();
      this->u = mem.alloc<double>(n);
      this->gradU = mem.alloc<double>(n);
    };

    ~FieldDif() {
      #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG  
      mem.dealloc<double>(&this->u);
      mem.dealloc<double>(&this->gradU);
    }

};
//******************************************************************************

/*******************************************************************************
 *@class Field
 *******************************************************************************
 *@brief     Classe dos campos de variaveis do problema de transporte.
 *@details   Classe dos campos de variaveis do problema de transporte. Os campos<!--
 *-->        são u, gradU e velocity.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class FieldTransp : public FieldDif {

  private:
    double *velocity; /**< Campo de velocidade*/

  public:

    double* get_velocity(void) { return this->velocity; };

    void alloc(void) override {
      int n = this->get_n();
      this->velocity = mem.alloc<double>(n);
      this->FieldDif::alloc();
    };

    ~FieldTransp() {
      #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG  
      mem.dealloc<double>(&velocity);
      this->FieldDif::~FieldDif();
    }
};
//******************************************************************************
#endif