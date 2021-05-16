#ifndef PROP_H
#define  PROP_H

#include<cmath>
#include"GMemoria.h"


/*******************************************************************************
 *@class PropRef
 *******************************************************************************
 *@brief     Classe com as propriedade fisicas de referencia.
 *@details   Esta classe guarda a propriedades físicas de referencia
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class PropRef {

  private:
    double rho;
    double cp;
    double ceofDif;

  public:

    // ... setters
    void set_rho(double value) { this->rho = value; }

    void set_cp(double value) { this->cp = value; }

    void set_ceofDif(double value) { this->ceofDif = value; }

    // ... getters
    double get_rho(void) { return this->rho; }

    double get_cp(void) { return this->cp; }

    double get_ceofDif(void) { return this->ceofDif; }

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
  double *rho; /**< Massa específica*/
  double *cp;  /**< Calor específico*/
  double *ceofDif;   /**< Coeficiente de difusão*/

public:

  // ... getters
 /**************************************************************************
  * @brief Obtém o array da massa específica
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_rho(void) { return this->rho; }
  
 /**************************************************************************
  * @brief Obtém o array da calor específico
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_cp(void) { return this->cp; }
  
 /**************************************************************************
  * @brief Obtém o array do coeficiente de difusao  
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      2021 - 2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_ceofDif(void) { return this->ceofDif; }
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
    this->ceofDif = mem.alloc<double>(n);
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
      this->ceofDif[i]   = propRef.get_ceofDif();
    }
  }
  // ..........................................................................

 /**************************************************************************
  * @brief Atualiza os coeficientes de difusao
  **************************************************************************/
  void updateCoefDif(const double* const u, unsigned int const n);
  /**************************************************************************
  * @brief Atualiza a massa especifica
  **************************************************************************/
  void updateRho(const double* const u, unsigned int const n);

  // ... Destrutor
  ~Prop() {
    #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << std::endl;
    #endif // DEBUG    
    mem.dealloc<double>(&this->rho);
    mem.dealloc<double>(&this->cp);
    mem.dealloc<double>(&this->ceofDif);
  }
  // ..........................................................................
};
#endif
