#include"../include/Prop.h"

static double polinomio(const double* const a, double const u,
                        short const nTerms ) {

  double tmp;

  tmp = a[0];
  for(int i = 0; i < nTerms; i++) {
    tmp += a[i]*pow(u, i);
  }

  return tmp;

}

/***************************************************************************
 *@details Atualiza os coeficientes de difusao em funcao de u               
 ***************************************************************************
 *@param u - Valores de u
 *@param n - Número de posicoes no vetor u
 ***************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
void Prop::updateCoefDif(const double* const u, unsigned int const n) {

  double* const coefDif = this->ceofDif;
  double const a[] = {1.0, 0.0000, 0.0000};

  for (int i = 0; i < n; i++) {
    coefDif[i] = polinomio(a, u[i], 2);
  }

}

/***************************************************************************
 *@details Atualiza a massa especifica em funcao de u
 ***************************************************************************
 *@param u - Valores de u
 *@param n - Número de posicoes no vetor u
 ***************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
void Prop::updateRho(const double* const u, unsigned int const n) {

  double* const rho = this->rho;
  double const a[] = { 2.0, 0.0000, -0.0000 };

  for (int i = 0; i < n; i++) {
    rho[i] = polinomio(a, u[i], 2);
  }

}