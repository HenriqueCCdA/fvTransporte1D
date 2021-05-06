#ifndef PROP_H
#define  PROP_H

#include"../include/GerenciadoDeMemoria.h"

/*******************************************************************************
 *@class PropRef
 *******************************************************************************
 *@brief     Classe com as propriedade fisicas de referencia.
 *@details   Esta classe guarda a propriedades f�sicas de referencia
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class PropRef {

  private:
    double rho;
    double cp;
    double k;

  public:

    // ... setters
    void set_rho(double value) { this->rho = value; }

    void set_cp(double value) { this->cp = value; }

    void set_k(double value) { this->k = value; }

    // ... getters
    double get_rho(void) { return this->rho; }

    double get_cp(void) { return this->cp; }

    double get_k(void) { return this->k; }

};

/*******************************************************************************
 *@class Prop
 *******************************************************************************
 *@brief     A Classe com as propriedade fisicas do dominio              
 *@details   A Classe com as propriedade fisicas do dominio 
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/

class Prop {

private:
  double *rho; /**< Massa espec�fica*/
  double *cp;  /**< Calor espec�fico*/
  double *k;   /**< Coeficiente de difus�o*/

public:

  // ... getters
 /**************************************************************************
  * @brief Obt�m o array da massa espec�fica
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_rho(void) { return this->rho; }
  
 /**************************************************************************
  * @brief Obt�m o array da calor espec�fico
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_cp(void) { return this->cp; }
  
 /**************************************************************************
  * @brief Obt�m o array do coeficiente de difusao  
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_k(void) { return this->k; }
  // ..........................................................................


  // ... metodos

  /**************************************************************************
  * @brief Aloca os arranjos para as propriedades fisicas
  **************************************************************************
  * @param n - tamanho o arranjo
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  void alloc(int n) {
    this->rho = mem.alloc<double>(n);
    this->cp = mem.alloc<double>(n);
    this->k = mem.alloc<double>(n);    
  }

  /**************************************************************************
  * @brief Inicializa as propriedades fisicas
  **************************************************************************
  * @param PropRef - propriedades de referencia
  * @param n       - tamanho o arranjo
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  void init_prop(PropRef &propRef, int n) {
    for (int i = 0; i < n; i++){
      this->rho[i] = propRef.get_rho();
      this->cp[i]  = propRef.get_cp();
      this->k[i]   = propRef.get_k();
    }
  }
  // ..........................................................................

  // ... Destrutor
  ~Prop() {
    #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << endl;
    #endif // DEBUG    
    mem.dealloc<double>(&this->rho);
    mem.dealloc<double>(&this->cp);
    mem.dealloc<double>(&this->k);
  }
  // ..........................................................................
};
#endif
