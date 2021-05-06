#ifndef NODE_H
#define NODE_H

#include"GerenciadoDeMemoria.h"

#include<iostream>

using namespace std;

/*******************************************************************************
 *@class Nodes
 *******************************************************************************
 *@brief     A Classe com as informa��es as n�s.
 *@details   Esta classe tema as inform��o e funcionalidades para lidar com     <--
 *<--        os n�s.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField>class Nodes{

  private:
    int nNodes; /**< N�mero de n�s*/
    double *x;  /**< Coordenada nodais*/
    TField fields; /**< Campo das variaveis*/ 

  public:

    TField& get_fields(void) { return this->fields; };

    // ... setters
    void set_nNodes(int d) { this->nNodes = d; }
    // ..........................................................................

    // ... getters
    int get_nNodes(void) { return this->nNodes; }

    double* get_x() { return this->x; }
    // ..........................................................................
    
    // ... metodos

    /***************************************************************************
     * @brief Aloca mem�ria para os arranjos x     
     **************************************************************************
     * @param n - Dimens�o dos arranjos
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    void alloc(int n) {
      this->x = mem.alloc<double>(n);
    }
    // ..........................................................................

    // ... detrutor
    /***************************************************************************
     * @brief Destrutor
     * @details Este destrutor libera a mem�ria utilizada nos arranjos x e   <!--
     * -->     u.
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    ~Nodes() {
      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG
      mem.dealloc<double>(&this->x);
    }
    // ..........................................................................

};
#endif