#ifndef POLINOMIO_H
#define POLINOMIO_H

#include<cmath>

const short nTermPolMax = 20; /**< Numero maximo de termos no polinomio*/


/*******************************************************************************
 *@class Polinomio
 *******************************************************************************
 *@brief     A Classe que implementa a interpolação via polinomio de ordem n
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Polinomio {

  private:  
    short nTerm;          /**< Numero de termo no polinomio*/
    double a[nTermPolMax];/**< Coeficientes do polinomio*/

  public:

    void set_nTerm(short nTerm){this->nTerm = nTerm;};
    
    void set_a(const double* const a, short nTerm); 

    void set_a(const double* const a); 

    double polinomio(double const x);

};

#endif
