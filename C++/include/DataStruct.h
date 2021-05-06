#ifndef DATASTRUCT_H
#define DATASTRUCT_H

/*******************************************************************************
 *@class DataStruct
 *******************************************************************************
 *@brief     Classe para uma estrutura de dados gen�rica para a matriz.
 *@details   Classe para uma estrutura de dados gen�rica para a matriz.     <!--
 *-->        Esta classe visa se herdada por outras classes     
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class DataStruct {

private:
  int n; /**< N�mero linhas na matriz*/

public:
  virtual void alloc(void) = 0;

  // ... setters
  void set_n(int n) { this->n = n; }
  // ..........................................................................

  // ... getters
  int get_n(void) { return n; };
  // ..........................................................................

  virtual ~DataStruct() {
    #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << std::endl;
    #endif // DEBUG 
  };

};

/*******************************************************************************
 *@class TriaDiagonal
 *******************************************************************************
 *@brief     Classe para uma estrura de dados triadigonal.
 *@details   Classe para uma estrura de dados triadigonal. Esta classe      <!--
 *-->        filha da classe DataStruct. 
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class TriaDiagonal : public DataStruct {
private:
  double *b; /**< Vetor de for�a do sistema de equa��es*/  
  double *l; /**< Diagonal inferior da matriz*/ 
  double *d; /**< Diagonal principal da matriz*/
  double *u; /**< Diagonal superior da matriz*/ 
public:

  // ... Construtor
  /***************************************************************************
   *@brief Contrutor
   *@details Este construtor aloca os vetores b, l, d e u do sistema de  <!--
   * -->     equa��es.
   **************************************************************************
   *@param n - N�meros de linhas de equ��es 
   **************************************************************************
   *@date      19/04/2021 - 25/04/2021
   *@author    Henrique C. C. de Andrade
   ***************************************************************************/
  TriaDiagonal(int nEq) {
    this->set_n(nEq);
    this->alloc();
  }
  // ..........................................................................

  // ...metodos
  /******************************************************************************
   *@brief     Alloca��o da memoria utilizada na estrutura de dados tridiagonal.
  ***************************************************************************/
  void alloc(void) override;

  // ... setters
  void set_n(int nEq) { this->DataStruct::set_n(nEq); }
  // ..........................................................................

  // ... getters
  int get_n(void) { return this->DataStruct::get_n(); }

  /***************************************************************************
  * @brief Obtem o arranjo da diagonal inferior da matriz
  ****************************************************************************
  * @return retorna um ponteiro para l
  ****************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_l(void) { return this->l; }

  /***************************************************************************
  * @brief Obtem o arranjo da diagonal principal da matriz
  ****************************************************************************
  * @return retorna um ponteiro para d
  ****************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_d(void) { return this->d; }

  /***************************************************************************
  * @brief Obtem o arranjo da diagonal superior da matriz
  ****************************************************************************
  * @return retorna um ponteiro para u
  ****************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ***************************************************************************/
  double* get_u(void) { return this->u; }

  /*****************************************************************************
  * @brief Obtem o arranjo da vetor de for�as                               
  ******************************************************************************
  * @return retorna um ponteiro para b                                      
  ******************************************************************************
  * @date      19/04/2021 - 25/04/2021                                      
  * @author    Henrique C. C. de Andrade                                    
  *****************************************************************************/
  double* get_b(void) { return this->b; }
  // ..........................................................................

  // ... detrutor
  /*****************************************************************************
   * @brief Destrutor
   * @details Este destrutor libera a memoria utilizada nos arranjos b, l, d e u
   *****************************************************************************
   * @date      19/04/2021 - 25/04/2021
   * @author    Henrique C. C. de Andrade
   *****************************************************************************/
  ~TriaDiagonal() {

    #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << std::endl;
    #endif // DEBUG 
    
    mem.dealloc<double>(&this->b);
    mem.dealloc<double>(&this->l);
    mem.dealloc<double>(&this->d);
    mem.dealloc<double>(&this->u);
  }
  // ..........................................................................
};
#endif
