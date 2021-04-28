#ifndef EPDSOLVER_H
#define EPDSOLVER_H

#include<iostream>

#include"Files.h"
#include"Mesh.h"
#include"Prop.h"
#include"IntTemp.h"
#include"CellLoop.h"
#include"Writer.h"

using namespace std;

/*******************************************************************************
 *@class EpdSolver
 *******************************************************************************
 *@brief     Classe para a solução da equações diferencial                
 *@details   Classe para a solução da equações diferencial. O objeto de     <!--
 *-->        classe utiliza referencias para os objetos do tipo mesh        <!--
 *-->        intTemp, cellLoop e solver.                                     
 *******************************************************************************
 *@date      19 / 04 / 2021 - 25 / 04 / 2021
 *@author    Henrique C.C.de Andrade
 *******************************************************************************/
class EpdSolver {

  private:
    Mesh *mesh;          /**< Objeto para malha*/
    IntTemp *intTemp;    /**< Objeto para integração temporal*/
    CellLoop *cellLoop;  /**< Objeto para loop nas células*/
    Solver *solverEq;    /**< Objeto para o solver do sistema de equações*/
    Writer *writer;      /**< Objeto para escrita de resultados*/
  public:

    // ... Construtor
    /***************************************************************************
     *@brief Contrutor
     *@details Este construtor recebe referencias para mesh, inTemp         <!--
     *         , cellLoop e solver.                    
     ***************************************************************************
     *@param mesh     - Malha utilizada
     *@param intTemp  - Integração temporal
     *@param cellLoop - Loop no tipo de célula desejado
     *@param solver   - Solver do sistema de equações
     ***************************************************************************
     *@date      19/04/2021 - 25/04/2021
     *@author    Henrique C. C. de Andrade
     ***************************************************************************/
    EpdSolver(Mesh *mesh, IntTemp *intTemp,
              CellLoop *cellLoop, Solver *solver, Writer *writer) {
      this->mesh = mesh;
      this->intTemp = intTemp;      
      this->cellLoop = cellLoop;
      this->solverEq = solver;
      this->writer = writer;
    }

   /***************************************************************************
    *@brief Inicialação dos dado para procedimento de solução da EDP.
    ***************************************************************************/
    void init(void);
    
   /***************************************************************************
    *@brief Procedimento principal da solução da EDP.                       
    ***************************************************************************/
    void solver(void);

};
#endif