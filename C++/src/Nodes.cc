#include"../include/Nodes.h"

/***************************************************************************
 * @details Faz a interpolação do valores da celula para o nos  
 **************************************************************************
 * @param n - Dimensão dos arranjos
 **************************************************************************
 * @date      2021 - 2021
 * @author    Henrique C. C. de Andrade
***************************************************************************/
template<class TField>
void Nodes<TField>::interpol(double* const nValue, const double* const cValue,
                            const int* const cells,
                            int const nNodes, int const nCells) {

  // ...
  for (int i = 0; i < nNodes; i++)
    nValue[i] = 0.e0;
  // .........................................................................

  // ...
  int no1, no2;
  for (int i = 0; i < nCells; i++) {
    no1 = cells[2 * i];
    no2 = cells[2 * i + 1];
    nValue[no1] += cValue[i];
    nValue[no2] += cValue[i];
  }
  // ..........................................................................

  // ...
  for (int i = 1; i < nNodes - 1; i++)
    nValue[i] *= 0.5e0;
  // ..........................................................................

}
/*****************************************************************************/
// ...
template class Nodes<FieldDif>;
// ............................................................................