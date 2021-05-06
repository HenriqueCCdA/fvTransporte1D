#ifndef NODE_H
#define NODE_H

#include"GerenciadoDeMemoria.h"

#include<iostream>

using namespace std;

/*******************************************************************************
 *@class Nodes
 *******************************************************************************
 *@brief     A Classe com as informações as nós.
 *@details   Esta classe tema as informção e funcionalidades para lidar com     <--
 *<--        os nós.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField>class Nodes{

  private:
    int nNodes; /**< Número de nós*/
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
     * @brief Aloca memória para os arranjos x     
     **************************************************************************
     * @param n - Dimensão dos arranjos
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
     * @details Este destrutor libera a memória utilizada nos arranjos x e   <!--
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