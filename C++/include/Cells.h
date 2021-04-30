#pragma once

#include"Prop.h"
#include"GerenciadoDeMemoria.h"


enum typeCell{
  line = 1 /**< Tipo de c�lula*/
};


/*******************************************************************************
 *@class Cells
 *******************************************************************************
 *@brief     A Classe com as informa��es as c�lulas.
 *@details   Classe com as informa��es das c�lulas.             
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/

class Cells {

  private:
    int nCells; /**< N�mero de c�lulas*/
    int *nodes; /**< Conectividades nodais das c�lulas Nodes[nCel,0] = no1 e Nodes[nCel,1] = no2*/
    double *u;  /**< Valores do campo escalar*/
    double *xc; /**< Valores dos centroides*/
    short *nNodesByCell; /**< Numeros de nos por celula*/
    short *type; /**< Tipo da celula*/
    double dx;  /**< Comprimento das celulas*/
    Prop prop;  /**< Propriedades fisicas por c�lulas*/      

  public:

    // ... setters
    /***************************************************************************
     * @brief Seta o comprimento da c�lulas
     ***************************************************************************
     * @param d - valor do comprimento
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_dx(double d) { this->dx = d; }

    /***************************************************************************
     * @brief Seta o n�mero de c�lulas 
     ***************************************************************************
     * @param d - valor do n�mero de c�lulas
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_nCells(int d) { this->nCells = d; }

    /***************************************************************************
     * @brief Seta o valor inicial de u
     ***************************************************************************
     * @param d - valor 
     * @param n - tamanho do arranjo 
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_u(double d, int n) {
      for (int i = 0; i < n; i++) {
        this->u[i] = d;
      }
    }
    // ..........................................................................

    // ... getters
   /***************************************************************************
     * @brief Retorna o comprimento das c�lulas
     ***************************************************************************
     * @return - valor do comprimento das c�lulas
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    double get_dx(void) { return this->dx; }

    /***************************************************************************
      * @brief Retorna uma referencia para objeto das propriedade f�sicas
      ***************************************************************************
      * @return - Referencia para o objeto
      ***************************************************************************
      * @date      19/04/2021 - 25/04/2021
      * @author    Henrique C. C. de Andrade
      ***************************************************************************/
    Prop& get_prop() { return this->prop; }

    /***************************************************************************
      * @brief Retorna o n�mero de c�lulas
      ***************************************************************************
      * @return - numero de c�lulas
      ***************************************************************************
      * @date      19/04/2021 - 25/04/2021
      * @author    Henrique C. C. de Andrade
      ***************************************************************************/
    int get_nCells(void) { return this->nCells; }

    /***************************************************************************
    * @brief Retorna o arranjos com os centroides
    ***************************************************************************
    * @return - ponteiro o arranjos com os centroides
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double* get_xc() { return this->xc; }

    /***************************************************************************
    * @brief Retorna o arranjos com os valores de u
    ***************************************************************************
    * @return - ponteiro o arranjos com os valores u 
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double* get_u() { return this->u; }

    /***************************************************************************
    * @brief Retorna o arranjos com os valores dos nos das c�lulas
    ***************************************************************************
    * @return - ponteiro o arranjos com os nos das c�lulas 
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    int* get_nodes() { return this->nodes; }
    // ..........................................................................

    /***************************************************************************
    * @brief Retorna o arranjos nNodesByCell
    ***************************************************************************
    * @return - ponteiro o arranjos com os numero de nos por c�lula
    ***************************************************************************
    * @date      19/04/2021 - 30/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    short* get_nNodesByCell() { return this->nNodesByCell; }
    // ..........................................................................

    /***************************************************************************
    * @brief Retorna o arranjos type           
    ***************************************************************************
    * @return - ponteiro o arranjos com o tipo das c�lulas            
    ***************************************************************************
    * @date      19/04/2021 - 30/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    short* get_type() { return this->type; }
    // ..........................................................................
    
    // ... metodos

    /***************************************************************************
     * @brief Aloca mem�ria para os arranjos xc, u, nodes, type, nNodesByCell   <!--
     * -->    e prop.
     ***************************************************************************
     * @param n - Dimens�o dos arranjos
     ***************************************************************************
     * @date      19/04/2021 - 30/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void alloc(int n) {
      
      this->type         = mem.alloc<short>(n);
      this->nNodesByCell = mem.alloc<short>(n);
      this->xc = mem.alloc<double>(n);
      this->u = mem.alloc<double>(n);
      this->nodes = mem.alloc<int>(2*n);

      this->prop.alloc(n);

    }
    // ..........................................................................

    // ... detrutor
    /***************************************************************************
     * @brief Destrutor
     * @details Este destrutor libera a mem�ria utilizada nos arranjos xc  <!--
     * -->    , u, nodes, nNodesByCell, type e prop.
     **************************************************************************
     * @date      19/04/2021 - 30/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    ~Cells() {
      mem.dealloc<short>(&this->type);
      mem.dealloc<short>(&this->nNodesByCell);
      mem.dealloc<double>(&this->xc);
      mem.dealloc<double>(&this->u);
      mem.dealloc<int>(&this->nodes);
      this->prop.~Prop();
    }
    // ..........................................................................

};