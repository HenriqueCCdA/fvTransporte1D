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
    string nameOut;      /**< Nome do arquivo de saida*/
    ofstream fileOutCell;/**< Arquivo de escrita com os valores por célula*/
    ofstream fileOutNode;/**< Arquivo de escrita com os valores por nó*/

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
    void set_nameOut(string name) { this->nameOut = name; }
    
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

    string get_nameOut(void) { return this->nameOut; }

    string get_nameIn(void) { return this->nameIn; }
    // ..........................................................................

    /***************************************************************************
    *@brief Leitura do dados iniciais.
    ***************************************************************************/
    void read(Mesh &mesh, IntTemp &intTemp);    
};


#endif