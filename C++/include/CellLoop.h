#ifndef CELLLOOP_H
#define CELLLOOP_H

enum cc { cce = 1, ccd = 2 };

/******************************************************************************
 *@class  CellLoop
 ******************************************************************************
 *@brief   A Classe loop nas células.
 *@details A Classe loop nas células e uma classe generica.
 ******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
class CellLoop {

  public:

    virtual void montaSistema(void)=0;
    virtual void gradients(void)=0;
    virtual void flux(void)=0;

    virtual ~CellLoop(){
      #ifdef DEBUG
      std::cout << "Destrutor: " << typeid(this).name() << std::endl;
      #endif // DEBUG 
    };

};

#endif
