#ifndef MEDIAS_H
#define MEDIAS_H

enum medias { 
             mediaSimple    = 1,  /**< Média simples.*/
             mediaPondera   = 2,  /**< Média ponderadas.*/
             mediaHarmonica = 3   /**< Média harmonica.*/
            };

/******************************************************************************
 *@class  Medias
 ******************************************************************************
 *@brief   A Classe com varios tipos de médias.                
 *@details A Classe com varios tipos de médias. Médias implementadas foram: <!--
 *-->      simple, pondera e harmonica.                                            
 *******************************************************************************
 *@date      2021-2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
class Medias {

  private:
    short cod; /**< Tipo de médias*/

  public:

    /*************************************************************************
    * @details Médias
    **************************************************************************
    * @param cod - Tipo da média
    **************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    Medias(short const cod) { this->cod = cod; }
    /***************************************************************************/

    /*************************************************************************
    * @details Médias
    **************************************************************************
    * @param phiP  - Valor de P
    * @param phiA  - Valor de A
    * @param alfPA - Parametro de ponderação
    * @return Retorna o valor da média
    **************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double medias(double const phiP, double const phiA,
                  double const alfPA = 0.5e0) {

      short cod = this->cod;

      if (cod == medias::mediaSimple) {
        return this->mediaSimples(phiP, phiA);      
      }else if(cod == medias::mediaPondera){
        return mediaPonderada(phiP, phiA, alfPA);
      }else if (cod == medias::mediaHarmonica) {
        return mediaHarmonica(phiP, phiA, alfPA);
      }

    }
    /***************************************************************************/
    
    /***************************************************************************
    * @details Médias ponderada
    ****************************************************************************
    * @param phiP  - Valor de P
    * @param phiA  - Valor de A
    * @return Retorna o valor da média
    ****************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ****************************************************************************/
    double mediaSimples(double const phiP, double const phiA) {

      return (phiP + phiA)*0.5e0;

    }
    /***************************************************************************/
    
    /***************************************************************************
    * @details Médias ponderada
    ****************************************************************************
    * @param phiP  - Valor de P
    * @param phiA  - Valor de A
    * @param alfPA - Parametro de ponderação
    * @return Retorna o valor da média
    ****************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ****************************************************************************/
    double mediaPonderada(double const phiP, double const phiA,
                          double const alfPA = 0.5e0) {

      return (1.e0 - alfPA)*phiP + alfPA * phiA;

    }
    /***************************************************************************/

    /***************************************************************************
    * @details Médias harmonica                                     
    ****************************************************************************
    * @param phiP  - Valor de P
    * @param phiA  - Valor de A
    * @param alfPA - Parametro de ponderação
    * @return Retorna o valor da média
    ****************************************************************************
    * @date      2021 - 2021
    * @author    Henrique C. C. de Andrade
    ****************************************************************************/
    double mediaHarmonica(double const phiP, double const phiA,
                          double const alfPA = 0.5e0) {
      double t1 = (1.e0 - alfPA)/phiA;
      double t2 = alfPA / phiP;

      return 1.e0/(t1 + t2);
    }
    /***************************************************************************/
};


#endif