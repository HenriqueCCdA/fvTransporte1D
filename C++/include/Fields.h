#ifndef FIELDS_H
#define FIELDS_H

class Field {

  private:
    int n;
    int ndf;
    int ndm;

  public:

  void set_n(int n){ this-> n = n};
  void set_ndf(int n) { this->ndf = n };
  void set_ndm(int n) { this->n = n };
  
  int get_n(void) { return this->n };
  int get_ndf(void) { return  this->ndf };
  int get_ndm(void) { return this->ndm};

  virtual void alloc(void) = 0;

};

class FieldDif : public Field {

  private:
    double *u;
    double *flux;

  public:

    void alloc(void) override{
      int n = this->get_n();
      this->u = mem.alloc<double>(n);
      this->flux = mem.alloc<double>(n);
    };

    ~Cells() {
      mem.dealloc<short>(&this->u);
      mem.dealloc<short>(&this->flux);
    }

};

class FieldTransp : public FieldDif {

  private:
    double *velocity;

  public:

    void alloc(void) override {
      int n = this->get_n();
      this->velocity = mem.alloc<double>(n);
      this->FieldDif::alloc(void);
    };

    ~Cells() {
      mem.dealloc<short>(&this->u);
      mem.dealloc<short>(&this->flux);
    }


#endif
