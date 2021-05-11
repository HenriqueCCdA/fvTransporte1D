#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>

#include"GMemoria.h"
#include"DataStruct.h"

using namespace std;

/*******************************************************************************
 *@class Solver                                                                 
 *******************************************************************************
 *@brief     A Classe que resolve um sistema de equa��es generico               
 *@details   A Classe que resolve um sistema de equa��es generico. Esta    <!--      
 *-->  classe tem como principal papel ser herdada.                        
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021                                                          
 *@author    Henrique C. C. de Andrade                                          
 *******************************************************************************/

class Solver {


  private:
    DataStruct *data; /**< Estrutura de dados do sistema de equa��es*/

  public:
    // ... getters    

    /**************************************************************************
     * @brief Obtem o n�mero de equa��es do sistema de equa��es
     **************************************************************************
     * @return retorna a n�mero de equa��es
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    int get_nEq(void)   { return this->get_dataStruct()->get_n(); }
    
    /***************************************************************************
     * @brief Obtem a estrura de dados utilizado
     ***************************************************************************
     * @return  retorna um ponteiro para a estrutura de dados
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    DataStruct* get_dataStruct(void){return this->data;}

    // ... setters 

    /***************************************************************************
     * @brief Set a estrutura de dados
     ***************************************************************************
     * @param data - Ponteiro para uma estrutura de dados
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_dataStruct(DataStruct* data) { this->data = data; }

    /***************************************************************************
     * @brief Solu��o do sistema de equa��es
     ***************************************************************************
     * @param x - solu��o inicial do solver
     ***************************************************************************
     * @return  retorna a solu��o do sistema de equa��es
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    virtual double* solver(double *x)=0;


    virtual ~Solver() {
      #ifdef DEBUG
        std::cout << "Destrutor: " << typeid(this).name() << endl;
      #endif // DEBUG 
    };
};
#endif
