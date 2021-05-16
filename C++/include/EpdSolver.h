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
 *@brief     Classe para a solu��o da equa��es diferencial                
 *@details   Classe para a solu��o da equa��es diferencial. O objeto de     <!--
 *-->        classe utiliza referencias para os objetos do tipo mesh        <!--
 *-->        intTemp, cellLoop e solver.                                     
 *******************************************************************************
 *@date      19 / 04 / 2021 - 25 / 04 / 2021
 *@author    Henrique C.C.de Andrade
 *******************************************************************************/
template <class TField> class EpdSolver {

  private:
    Mesh<TField> *mesh;  /**< Objeto para malha*/
    IntTemp *intTemp;    /**< Objeto para integra��o temporal*/
    CellLoop *cellLoop;  /**< Objeto para loop nas c�lulas*/
    Solver *solverEq;    /**< Objeto para o solver do sistema de equa��es*/
    Writer *writer;      /**< Objeto para escrita de resultados*/
    unsigned int maxIter;/**< M�ximo de itera��o do solver n�o linear*/
    double res0;         /**< Residuo inicial*/
    double tol;          /**< Tolerancia do solver na linear*/
    bool firstConverge;  /**< Primeira vez que a funcao convergencia � chamada*/
  public:

    // ... Construtor
    /***************************************************************************
     *@brief Contrutor
     *@details Este construtor recebe referencias para mesh, inTemp             <!--
     *         , cellLoop e solver.                    
     ***************************************************************************
     *@param mesh     - Malha utilizada
     *@param intTemp  - Integra��o temporal
     *@param cellLoop - Loop no tipo de c�lula desejado
     *@param solver   - Solver do sistema de equa��es
     *@param top      - Tolerancia do solver n�o linear
     *@param maxIter  - N�mero m�ximo de itera��es do solver n�o linaer
     ***************************************************************************
     *@date      19/04/2021 - 25/04/2021
     *@author    Henrique C. C. de Andrade
     ***************************************************************************/
    EpdSolver(Mesh<TField> *mesh, IntTemp *intTemp,
              CellLoop *cellLoop, Solver *solver, Writer *writer,
              double const tol = 1.e-6, double const maxIter = 10){
      this->mesh = mesh;
      this->intTemp = intTemp;      
      this->cellLoop = cellLoop;
      this->solverEq = solver;
      this->writer = writer;
      // ...
      this->tol = tol;
      this->maxIter = maxIter;
      this->res0 = 1.e0;
      this->firstConverge = true;
      // ......................................................................
    }

   /***************************************************************************
    *@brief Iniciala��o dos dado para procedimento de solu��o da EDP.
    ***************************************************************************/
    void init(void);
    
   /***************************************************************************
    *@brief Procedimento principal da solu��o da EDP.                       
    ***************************************************************************/
    void solver(void);

    /***************************************************************************
    *@brief Checa a convergencia do loop n�o linear do sistema de EDP.
    ***************************************************************************/
    bool convergence(short const it = 0, bool const plot = false);

    /***************************************************************************
    *@brief Atualiza a solu��o.
    ***************************************************************************/
    void updateU(void);

};
#endif