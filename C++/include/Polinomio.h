#ifndef POLINOMIO_H
#define POLINOMIO_H

const short nTermMax = 20;

class Polinomio {

  private:  
    short nTerm;
    double a[nTermMax];

  public:

    void set_nTerm(short nTerm){this->nTerm = nTerm;};
    
    void set_a(const double* const a, short nTerm) {
      this->set_nTerm(nTerm);
      this->set_a(a);
    }

    void set_a(const double* const a) {
      for (int i = 0; i < this->nTerm; i++) {
        this->a[i] = a[i];
      }
    }

    double polinomio(double const u) {

      double tmp;

      tmp = a[0];
      for (int i = 0; i < this->nTerm; i++) {
        tmp += this->a[i] * pow(u, i);
      }

      return tmp;

    }


};

#endif
