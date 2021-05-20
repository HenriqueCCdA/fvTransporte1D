#include"../include/GMemoria.h"

/**************************************************************************
 *@details Aloca um arranjo de tamanho n. Este metodo utiliza new para      <--
 *-->      a alocação da mémoria
 ***************************************************************************
 * @param numero de termos solicitados
 * @return retorna um ponteiro alocado no heap
 ***************************************************************************
 * @date      19/04/2021 - 25/04/2021
 * @author    Henrique C. C. de Andrade
 ***************************************************************************/
template<typename T> T* Memoria::alloc(size_t n, std::string name) {

  T *p = nullptr;

  if (n <= 0) {
    std::cout << "Mem: Numero nulo ou negativo de posicoes !!" << std::endl;
    exit(error::dimArraySize);
  }

  p = new (std::nothrow) T[n];

  //... 
  int nn = Memoria::countArrays;
  this->names[nn] = name + std::to_string(nn);
  this->px[nn][0] = &p[0];
  this->px[nn][1] = &p[n - 1];
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
/**************************************************************************/

/**************************************************************************
*@details Desaloca um arranjo alocado pelo método new.
***************************************************************************
* @param x - Endereção do ponteiro alocado
***************************************************************************
* @date      2021 - 2021
* @author    Henrique C. C. de Andrade
***************************************************************************/
template<typename T>  void Memoria::dealloc(T **x) {

  delete[] * x;

  *x = nullptr;

  //... 
  int nn = Memoria::countArrays;
  this->names[nn] = "";
  this->px[nn][0] = nullptr;
  this->px[nn][1] = nullptr;
  this->type[nn] = "";
  this->pos[nn] = 0;
  // ....................................................................... 
  
  if(Memoria::countArrays > 0)
    Memoria::countArrays--;
}
/**************************************************************************/

// ...
template short* Memoria::alloc(size_t n, std::string name);
template void Memoria::dealloc(short**);

template int* Memoria::alloc(size_t n, std::string name);
template void Memoria::dealloc(int**);

template double* Memoria::alloc(size_t n, std::string name);
template void Memoria::dealloc(double**);
// ............................................................................