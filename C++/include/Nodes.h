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
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Nodes{

  private:
    int nNodes; /**< N�mero de n�s*/
    double *x;  /**< Coordenada nodais*/
    double *u;  /**< Valores do campo escalor por de n�s*/

  public:
    // ... setters
    void set_nNodes(int d) { this->nNodes = d; }

    void set_u(double d, int n) {
      for (int i = 0; i < n; i++){
        this->u[i] = d;
      }
    }
    // ..........................................................................

    // ... getters
    int get_nNodes(void) { return this->nNodes; }

    double* get_x() { return this->x; }

    double* get_u() { return this->u; }
    // ..........................................................................
    
    // ... metodos

    /***************************************************************************
     * @brief Aloca mem�ria para os arranjos c e u
     **************************************************************************
     * @param n - Dimens�o dos arranjos
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    void alloc(int n) {
      this->x = mem.alloc<double>(n);
      this->u = mem.alloc<double>(n);
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
      mem.dealloc<double>(&this->x);
      mem.dealloc<double>(&this->u);
    }
    // ..........................................................................

};
#endif