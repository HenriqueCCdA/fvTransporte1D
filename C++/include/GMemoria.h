#ifndef GMEM_H
#define GMEM_H

#include<iostream>
#include<string>
#include"Error.h"

const int nArrays = 200;  /**< Numero de maximo de arrays que podem ser alocados*/

/*******************************************************************************
 *@class Memoria
 *******************************************************************************
 *@brief     A Classe que gerencia a alocação de mémoria.
 *@details   A Classe que gerencia a alocação de mémoria.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Memoria {
  
  private:
    static int countArrays;
    std::string names[nArrays];  
    void* px[nArrays][2];
    std::string type[nArrays];
    int pos[nArrays];

  public:

    /**************************************************************************
    *@brief Aloca um arranjo                                                   
    ***************************************************************************/
    template<typename T> T* alloc(size_t n, std::string name = "a");;

    /**************************************************************************
    *@brief Desaloca um arranjo
    ***************************************************************************/
    template<typename T>  void dealloc(T **x); 

};

extern Memoria mem;

#endif