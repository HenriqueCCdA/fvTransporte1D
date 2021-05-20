#ifndef PROP_H
#define  PROP_H

#include<cmath>

#include"GMemoria.h"
#include"Polinomio.h"

enum typePropVar{
  cte  = 1, /**< Valor constante*/
  varU = 2  /**< Variacao com U */
};

/*******************************************************************************
 *@class PropPhisicy
 *******************************************************************************
 *@brief     Classe com que definine uma proriedade fisicas.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class PropPhisicy {

  private:
    bool update;
    int n;
    short type;
    double *value = nullptr;
    double valueCte;
    Polinomio pol;

  public:

    // ... setters
    void set_n(int value) { this->n = value; }

    void set_type(short type) { 
      this->type = type;
      if (this->type == typePropVar::cte)
        this->update = false;
      else
        this->update = true;
    }

    // ... setters
    void set_valueCte(double const value) { this->valueCte = value; }

    void set_value(double const u) {
      if(this->type == typePropVar::cte){
        for (int i = 0; i < this->n; i++) {
          this->value[i] = this->valueCte;
        }
      }
      else if (this->type == typePropVar::varU) {
        for (int i = 0; i < this->n; i++) {
          this->value[i] = this->pol.polinomio(u);
        }
      }
    }

    // ... getters
    double* get_value(void) { return this->value;}
    Polinomio* get_pol(void) { return &this->pol;}

    bool isToUpdate(void) { return this->update;}

    void init(double const u, int const n) {
      this->set_n(n);
      this->alloc();
      this->set_value(u);
    }


    void alloc(void) {
      this->value = mem.alloc<double>(this->n);
    }

    void dealloc() {
       if (this->type == typePropVar::varU)
         mem.dealloc<double>(&value);
    }

    // ... Destrutor
    ~PropPhisicy() {
      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << std::endl;
      #endif // DEBUG    
    }
    // ..........................................................................

};


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
  double *cp = nullptr;        /**< Calor específico*/
  PropPhisicy rho;     /**< Massa específica*/
  PropPhisicy coefDif;  /**< Coeficiente de difusão*/

public:

  // ... getters
 /**************************************************************************
  * @brief Obtém o array da massa específica
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      2021 - 2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  PropPhisicy* get_rho(void){ return &rho;};

  /**************************************************************************
  * @brief Obtém o array do coeficiente de difusao
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      2021 - 2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  PropPhisicy* get_coefDif(void) { return &coefDif; };

 /**************************************************************************
  * @brief Obtém o array da calor específico
  **************************************************************************
  * @return retorna o ponterio
  **************************************************************************
  * @date      2021 - 2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_cp(void) { return this->cp; }
 
  // ..........................................................................


  // ... metodos

  /**************************************************************************
  * @brief Aloca os arranjos para as propriedades fisicas
  **************************************************************************
  * @param n - tamanho o arranjo
  **************************************************************************
  * @date      2021 - 2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  void alloc(int n) {
    this->cp = mem.alloc<double>(n);
  }

  /**************************************************************************
  * @brief Inicializa as propriedades fisicas
  **************************************************************************
  * @param u - valor u                     
  * @param n - tamanho o arranjo
  **************************************************************************
  * @date      2021 - 2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  void init_prop(double u0, int n) {
    for (int i = 0; i < n; i++){
      this->cp[i]  = 1.0;
    }

    this->rho.init(u0, n);
    this->coefDif.init(u0, n);

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
    mem.dealloc<double>(&this->cp);
    this->coefDif.dealloc();
    this->rho.dealloc();
  }
  // ..........................................................................
};



#endif
