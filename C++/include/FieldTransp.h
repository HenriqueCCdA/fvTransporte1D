#ifndef FIELDTRANSP_H
#define FIELDTRANSP_H

#include"FieldDif.h"

/*******************************************************************************
 *@class Field
 *******************************************************************************
 *@brief     Classe dos campos de variaveis do problema de transporte.
 *@details   Classe dos campos de variaveis do problema de transporte. Os campos<!--
 *-->        são u, gradU e velocity.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class FieldTransp : public FieldDif {

private:
  double *velocity; /**< Campo de velocidade*/

public:

  double* get_velocity(void) { return this->velocity; };

  void alloc(void) override {
    int n = this->get_n();
    this->velocity = mem.alloc<double>(n);
    this->FieldDif::alloc();
  };

  ~FieldTransp() {
#ifdef DEBUG
    std::cout << "Destrutor: " << typeid(this).name() << std::endl;
#endif // DEBUG  
    mem.dealloc<double>(&velocity);
    this->FieldDif::~FieldDif();
  }
};
//******************************************************************************

#endif
