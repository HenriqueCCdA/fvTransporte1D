#pragma once

#include"Fields.h"
#include"Prop.h"
#include"GMemoria.h"


enum typeCell{
  line = 1 /**< Tipo de célula*/
};


/*******************************************************************************
 *@class Cells
 *******************************************************************************
 *@brief     A Classe com as informações as células.
 *@details   Classe com as informações das células.             
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField> class Cells {

  private:
    int nCells; /**< Número de células*/
    int *nodes; /**< Conectividades nodais das células Nodes[nCel,0] = no1 e Nodes[nCel,1] = no2*/
    double *xc; /**< Valores dos centroides*/
    double *residuo; /**< Resido na celula*/
    short *nNodesByCell; /**< Numeros de nos por celula*/
    short *type; /**< Tipo da celula*/
    double dx;  /**< Comprimento das celulas*/
    Prop prop;  /**< Propriedades fisicas por células*/      
    TField fields; /**< Campo das variaveis*/ 

  public:    

    // ... setters

    /***************************************************************************
     * @brief Seta o comprimento da células
     ***************************************************************************
     * @param d - valor do comprimento
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_dx(double d) { this->dx = d; }

    /***************************************************************************
     * @brief Seta o número de células 
     ***************************************************************************
     * @param d - valor do número de células
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_nCells(int d) { this->nCells = d; }

   // ... getters
   TField& get_fields(void) { return this->fields; };

   /***************************************************************************
     * @brief Retorna o comprimento das células
     ***************************************************************************
     * @return - valor do comprimento das células
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    double get_dx(void) { return this->dx; }

    /***************************************************************************
      * @brief Retorna uma referencia para objeto das propriedade físicas
      ***************************************************************************
      * @return - Referencia para o objeto
      ***************************************************************************
      * @date      19/04/2021 - 25/04/2021
      * @author    Henrique C. C. de Andrade
      ***************************************************************************/
    Prop& get_prop() { return this->prop; }

    /***************************************************************************
      * @brief Retorna o número de células
      ***************************************************************************
      * @return - numero de células
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
    * @brief Retorna o arranjos com os valores dos nos das células
    ***************************************************************************
    * @return - ponteiro o arranjos com os nos das células 
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    int* get_nodes() { return this->nodes; }
    // ..........................................................................

    /***************************************************************************
    * @brief Retorna o arranjos nNodesByCell
    ***************************************************************************
    * @return - ponteiro o arranjos com os numero de nos por célula
    ***************************************************************************
    * @date      19/04/2021 - 30/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    short* get_nNodesByCell() { return this->nNodesByCell; }
    // ..........................................................................

    /***************************************************************************
    * @brief Retorna o arranjos type           
    ***************************************************************************
    * @return - ponteiro o arranjos com o tipo das células            
    ***************************************************************************
    * @date      19/04/2021 - 30/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    short* get_type() { return this->type; }
    // ..........................................................................
    
    /***************************************************************************
    * @brief Retorna o ponteiro para o arranjo de residuo por celula
    ***************************************************************************
    * @return - valor do comprimento das células
    ***************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double* get_residuo(void) { return this->residuo; }
    // ..........................................................................

    // ... metodos

    /***************************************************************************
     * @brief Aloca memória para os arranjos xc, u, nodes, type, nNodesByCell   <!--
     * -->    e prop.
     ***************************************************************************
     * @param n - Dimensão dos arranjos
     ***************************************************************************
     * @date      19/04/2021 - 30/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void alloc(int n) {
      
      this->type         = mem.alloc<short>(n);
      this->nNodesByCell = mem.alloc<short>(n);
      this->xc = mem.alloc<double>(n);
      this->residuo = mem.alloc<double>(n);
      this->nodes = mem.alloc<int>(2*n);

      this->prop.alloc(n);

    }

    /***************************************************************************
    * @brief Atualizao as propriedades                                     
    ***************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    void updateProp(void) {
      const double* const u = this->fields.get_u();
      unsigned int const n = this->get_nCells();

      this->prop.updateCoefDif(u, n);
      this->prop.updateRho(u, n);
    }
    // ..........................................................................

    // ... detrutor
    /***************************************************************************
     * @brief Destrutor
     * @details Este destrutor libera a memória utilizada nos arranjos xc  <!--
     * -->    , u, nodes, nNodesByCell, type e prop.
     **************************************************************************
     * @date      2021 - 2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    ~Cells() {

      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG     

      mem.dealloc<short>(&this->type);
      mem.dealloc<short>(&this->nNodesByCell);
      mem.dealloc<double>(&this->xc);
      mem.dealloc<double>(&this->residuo);
      mem.dealloc<int>(&this->nodes);
//    this->prop.~Prop();
    }
    // ..........................................................................

};