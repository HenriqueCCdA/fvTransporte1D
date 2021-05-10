#include"../include/FieldDif.h"

void FieldDif::set_u(double const value) {
  for (int i = 0; i < this->get_n(); i++) {
    this->u[i] = value;
  }
}

void FieldDif::set_gradU(double const value) {
  for (int i = 0; i < this->get_n(); i++) {
    this->gradU[i] = value;
  }
}

void FieldDif::alloc(void){
  int n = this->get_n();
  this->u = mem.alloc<double>(n);
  this->gradU = mem.alloc<double>(n);
  this->flux = mem.alloc<double>(n);
};

FieldDif::~FieldDif() {
#ifdef DEBUG
  std::cout << "Destrutor: " << typeid(this).name() << std::endl;
#endif // DEBUG  
  mem.dealloc<double>(&this->u);
  mem.dealloc<double>(&this->gradU);
  mem.dealloc<double>(&this->flux);
}