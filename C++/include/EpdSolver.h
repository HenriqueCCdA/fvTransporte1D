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
template <class TField> class EpdSolver {

  private:
    Mesh<TField> *mesh;  /**< Objeto para malha*/
    IntTemp *intTemp;    /**< Objeto para integração temporal*/
    CellLoop *cellLoop;  /**< Objeto para loop nas células*/
    Solver *solverEq;    /**< Objeto para o solver do sistema de equações*/
    Writer *writer;      /**< Objeto para escrita de resultados*/
    unsigned int maxIter;/**< Máximo de iteração do solver não linear*/
    double res0;         /**< Residuo inicial*/
    double tol;          /**< Tolerancia do solver na linear*/
    bool firstConverge;  /**< Primeira vez que a funcao convergencia é chamada*/
  public:

    // ... Construtor
    /***************************************************************************
     *@brief Contrutor
     *@details Este construtor recebe referencias para mesh, inTemp             <!--
     *         , cellLoop e solver.                    
     ***************************************************************************
     *@param mesh     - Malha utilizada
     *@param intTemp  - Integração temporal
     *@param cellLoop - Loop no tipo de célula desejado
     *@param solver   - Solver do sistema de equações
     *@param top      - Tolerancia do solver não linear
     *@param maxIter  - Número máximo de iterações do solver não linaer
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
    *@brief Inicialação dos dado para procedimento de solução da EDP.
    ***************************************************************************/
    void init(void);
    
   /***************************************************************************
    *@brief Procedimento principal da solução da EDP.                       
    ***************************************************************************/
    void solver(void);

    /***************************************************************************
    *@brief Checa a convergencia do loop não linear do sistema de EDP.
    ***************************************************************************/
    bool convergence(short const it = 0, bool const plot = false);

    /***************************************************************************
    *@brief Atualiza a solução.
    ***************************************************************************/
    void updateU(void);

};
#endif