#ifndef MESH_H
#define MESH_H

#include<fstream>
#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>

#include"Nodes.h"
#include"Cells.h"
#include"CcCi.h"
#include"Prop.h"
#include"IntTemp.h"

using namespace std;

/*******************************************************************************
 *@class Mesh
 *******************************************************************************
 *@brief   Classe para a malha.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField> class Mesh{

  private:
    double l;    /**< Dimensção do dominio*/
    Nodes<TField> nodes; /**< Nos da malha*/
    Cells<TField> cells; /**< Céluas  da malha*/
    CcCi  ccci;  /**< Condicoes de contorno*/
    IntTemp *intTemp;
    PropRef propRef;  

  public:

    Mesh(IntTemp *intTemp){
      this->intTemp = intTemp;
    }

    // ... getters
    PropRef& get_propRef(void) { return this->propRef; }

    Cells<TField>& get_cells(void) { return this->cells; }

    Nodes<TField>& get_nodes(void) { return this->nodes; }

    CcCi& get_ccci(void) { return this->ccci; }

    int get_nCells(void) { return this->get_cells().get_nCells(); }

    int get_nNodes(void) { return this->get_nodes().get_nNodes(); }

    double get_l(void) { return this->l; }   
    // ..........................................................................

    // ... setters
    void set_l(double d) { this->l = d; }
    // ..........................................................................

    // ... metodos
    /***************************************************************************
     *@brief Mostra informações importantes da malha.
     ***************************************************************************/
    void display(void);

    /***************************************************************************
     *@brief Aloca a memoria necessaria.
    ***************************************************************************/
    void alloc();

    /***************************************************************************
    *@brief Gera o grid.
    ***************************************************************************/
    void grid(void);

    /***************************************************************************
    *@brief Interpola valores das céluas para o nós.
    ***************************************************************************/
    void nodalInterpol(void);
};

#endif

