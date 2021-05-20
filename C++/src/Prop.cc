#include"../include/Prop.h"

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

  double* const coefDif = this->get_coefDif()->get_value();

  if(this->get_coefDif()->isToUpdate()){
    for (int i = 0; i < n; i++)
      coefDif[i] = this->get_coefDif()->get_pol()->polinomio(u[i]);
  }
  
}
/***************************************************************************/

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

  double* const rho = this->get_rho()->get_value();

  if (this->get_coefDif()->isToUpdate()){
    for (int i = 0; i < n; i++) 
      rho[i] = this->get_rho()->get_pol()->polinomio(u[i]);
  }    

}
/***************************************************************************/