#ifndef FIELDDIF_H
#define FIELDDIF_H

#include"Fields.h"

/*******************************************************************************
 *@class Field
 *******************************************************************************
 *@brief     Classe dos campos de variaveis do problema de difusão.
 *@details   Classe dos campos de variaveis do problema de difusão. Os campos   <!--
 *-->        são u e gradU.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class FieldDif : public Field {

private:
  double *u;    /**< Campo U*/
  double *gradU;/**< Campo gradiente do campo U*/
  double *flux; /**< Campo gradiente do flux*/

public:

  double* get_u(void) { return this->u; };
  
  double* get_u(short const level) {
    int desloc = this->get_n()* level;
    return &this->u[desloc];
  };

  double* get_gradU(void) { return this->gradU; };
  double* get_flux(void) { return this->flux; };

  void set_u(double const value);
  void set_u(double const value, short const level);
  void set_gradU(double const value);

  void alloc(short type) override;

  ~FieldDif();

};
//******************************************************************************

#endif
