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
    *@details Aloca um arranjo de tamanho n. Este metodo utiliza new para      <--
    *-->      a alocação da mémoria
    ***************************************************************************
    * @param numero de termos solicitados                                     
    * @return retorna um ponteiro alocado no heap
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/

    template<typename T> T* alloc(size_t n, std::string name = "a") {
       
       T *p = nullptr;    

       if (n<=0) {
         std::cout << "Mem: Numero nulo ou negativo de posicoes !!"<< std::endl;
         exit(error::dimArraySize);
       }

       p = new (std::nothrow) T[n];

       //... 
       int nn = Memoria::countArrays;
       this->names[nn] = name + std::to_string(nn);
       this->px[nn][0] = &p[0];
       this->px[nn][1] = &p[n-1];
       this->type[nn] = typeid(T).name();
       this->pos[nn] = n;
       // ....................................................................... 

       if (!p) {
          std::cout << "Mem: Arranjo nao pode ser alocado" << std::endl;
          exit(error::memory);
       }

       Memoria::countArrays++;
       return p;       
    }


    /**************************************************************************
    *@brief Desaloca um arranjo
    *@details Desaloca um arranjo alocado pelo método new.
    ***************************************************************************
    * @param x - Endereção do ponteiro alocado
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    template<typename T>  void dealloc(T **x) {
      delete[] *x;
      *x = nullptr;
      Memoria::countArrays--;
    }

};

extern Memoria mem;

#endif