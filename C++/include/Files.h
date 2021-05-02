#ifndef FILES_H
#define FILES_H

#include<string>
#include<iostream>
#include<fstream>

#include"IntTemp.h"
#include"Mesh.h"
#include"Error.h"

using namespace std;

/*******************************************************************************
 *@class Files
 *******************************************************************************
 *@brief     A Classe que gerencia os arquivos. 
 *@details    A Classe que gerencia os arquivo e entrada e saida. Operações <!--
 *-->         de leitura e escrita
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Files {

  private:
    string nameIn;       /**< Nome do arquivo de entrada*/
    string prefixNameOut;/**< Prefixo do Nome do arquivo de saida*/

  public:

    // ... setters
    /***************************************************************************
     * @brief Seta o nome do arquivo de saida
     ***************************************************************************
     * @param name - nome do arquivo
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_prefixNameOut(string name) { this->prefixNameOut = name; }
    
    /***************************************************************************
     * @brief Seta o nome do arquivo de entrada
     ***************************************************************************
     * @param name - nome do arquivo
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_nameIn(string name) { this->nameIn = name; }
    // ..........................................................................

    /***************************************************************************
    * @brief Retorna o nome do arquivo de saida
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    string get_prefixNameOut(void) { return this->prefixNameOut; }

    /***************************************************************************
    * @brief Retorna o nome do arquivo de entrada
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    string get_nameIn(void) { return this->nameIn; }
    // ..........................................................................

};


#endif