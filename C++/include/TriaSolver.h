#ifndef TRIASOLVER_H
#define TRIASOLVER_H

#include"Solver.h"

/******************************************************************************
 *@class TriSolver
 ******************************************************************************
 *@brief     A Classe que resolve um sistema de equa��es tridiagonais
 *@details   A Classe que resolve um sistema de equa��es tridiagonais. Esta <!--
 * -->  classe � filha da classe solver. Al�m dos vetores u, l, d e b       <!--
 * -->  do sistema de equac�es essas classe precisa dos vetores auxiliares  <!--
 * -->  um e bm. Todos esses vetores tem a dimenss�o igual a nEq.
 *******************************************************************************
 * @date      19/04/2021 - 25/04/2021
 * @author    Henrique C. C. de Andrade
 ******************************************************************************
*******************************************************************************/

class TriSolver : public Solver {

  private:
    
    // ...
    double *um = nullptr; /**< Arranjo auxiliar do solver tridiagonal*/
    double *bm = nullptr; /**< Arranjo auxiliar do solver tridiagonal*/
    // .......................................................................... 

    // ...
    double* tdma(double *x);
    // ..........................................................................

  public:

    // ... Contrutor
    
    /*************************************************************************** 
     *@brief Contrutor
     *@details Este construtor recebe um ponteiro para dataStruct. Al�m disso <!--
     * --> esse m�todo aloca os vetores um e bm.
     **************************************************************************          
     *@date      19/04/2021 - 25/04/2021
     *@author    Henrique C. C. de Andrade
    ***************************************************************************/ 
    TriSolver(DataStruct *data) {
      this->set_dataStruct(data);
      this->alloc();
    }
    // ..........................................................................

    // ... getters
    
    /***************************************************************************
     * @brief Obtem o n�mero de equa��es do sistema de equa��es
     **************************************************************************
     * @return retorna a n�mero de equa��es
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/ 
    int get_nEq(void) { return Solver::get_nEq(); }
    // ..........................................................................

    // ...metodos    
    void alloc(void);

    double* solver(double *x) override { return this->tdma(x); }
    // ..........................................................................

    // ... detrutor
    /***************************************************************************
     * @brief Destrutor
     * @details Este destrutor libera a memoria utilizada nos arranjos um e bm.
     **************************************************************************  
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    ~TriSolver() {
      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG 
     
      mem.dealloc<double>(&this->um);
      mem.dealloc<double>(&this->bm);
    }
    // ..........................................................................
};

#endif