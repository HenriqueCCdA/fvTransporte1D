#ifndef WRITER_H
#define WRITER_H

#include<fstream>
#include<string>

#include"../include/Mesh.h"
#include"../include/IntTemp.h"
#include"../include/VTK.h"

enum typeWriters {
  typeTXT = 1,  /**< Tipo do arquivo texto.*/
  typeVTK = 2   /**< Tipo do arquivo VTK.*/
};

/*******************************************************************************
 *@class Writer
 *******************************************************************************
 *@brief     A Classe que gerencia escrita dos os arquivos de resultado.
 *@details   A Classe que gerencia escrita dos os arquivos de resultado do.     <!--
 *-->        Esta classe é um classe abstrata
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Writer {

  private:
    string preName; /**< Nome do prefixo do arquivo*/

  public:

    virtual void write(void)=0;
    virtual void openOutputFile(void)=0;
    virtual void closeOutputFile(void)=0;

    string& get_preName(void){return this->preName;};

    void set_preName(string name) { this->preName = name; };
};


/*******************************************************************************
 *@class WriterTxt
 *******************************************************************************
 *@brief     A Classe que gerencia escrita dos os arquivos de resultado.
 *@details   A Classe que gerencia escrita dos os arquivos de resultado. O      <!--
 *-->        arquivo do tipo texto.            
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField>
class WriterTxt : public Writer {

private:
  string nameOutNode;  /**< Nome do arquivo de saida da nós*/
  string nameOutCell;  /**< Nome do arquivo de saida da células*/
  ofstream fileOutCell;/**< Arquivo de escrita com os valores por célula*/
  ofstream fileOutNode;/**< Arquivo de escrita com os valores por nó*/
  IntTemp *intTemp;    /**< Objeto para integração temporal*/
  Mesh<TField> *mesh;       /**< Objeto para a malha*/
  bool    firstCall;   /**< Guarda a primeira vez que o write é chamado*/
public:
  // ... Construtor
  /***************************************************************************
   *@brief Contrutor
   *@details Este construtor recebe referencias para mesh, inTemp         <!--
   *         , cellLoop e solver.
   ***************************************************************************
   *@param mesh     - Malha utilizada
   *@param intTemp  - Integração temporal
   *@param name     - o prefixo do arquivo de saida
   ***************************************************************************
   *@date      19/04/2021 - 25/04/2021
   *@author    Henrique C. C. de Andrade
   ***************************************************************************/
  WriterTxt(Mesh<TField>* mesh, IntTemp* intTemp, string name) {
    this->mesh = mesh;
    this->intTemp = intTemp;
    this->set_preName(name);
    this->firstCall = true;
  }

  /****************************************************************************
  * @brief Escreve os resultados.
  *****************************************************************************/
  void write(void) override;
  /****************************************************************************/

  /*****************************************************************************
  * @brief Fecha os arquivos de saida.
  ******************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ******************************************************************************/
  void closeOutputFile(void) override{
    fileOutNode.close();
    fileOutCell.close();
  }

  /****************************************************************************
   *@brief     Abre os arquivos de saida
   ****************************************************************************/
  void openOutputFile(void) override;

  /****************************************************************************
  *@brief Escreve os resultado nodais.
  *****************************************************************************/
  void resNode(Mesh<TField> &mesh, IntTemp &intTemp);

  /****************************************************************************
  *@brief Escreve coordenada dos nós.
  *****************************************************************************/
  void geomNode(Mesh<TField> &mesh);

  /****************************************************************************
  *@brief Escreve os resultado por células.
  *****************************************************************************/
  void resCell(Mesh<TField> &mesh, IntTemp &intTemp);

  /******************************************************************************
  *@brief Escreve as coordenada dos centraiodes.
  ******************************************************************************/
  void geomCell(Mesh<TField> &mesh);
  // ..........................................................................

  // ... getters
  /***************************************************************************
   * @brief Obtém a referencia do arquivo de saida para escrita
   ***************************************************************************
   * @return - referencia para o arquivo
   ***************************************************************************
   * @date      19/04/2021 - 25/04/2021
   * @author    Henrique C. C. de Andrade
   ***************************************************************************/
  ofstream& get_fileOutNode() { return this->fileOutNode; }

  /***************************************************************************
   * @brief Obtém a referencia do arquivo de saida para escrita
   ***************************************************************************
   * @return - referencia para o arquivo
   ***************************************************************************
   * @date      19/04/2021 - 25/04/2021
   * @author    Henrique C. C. de Andrade
   ***************************************************************************/
  ofstream& get_fileOutCell() { return this->fileOutCell; }

};


/*******************************************************************************
 *@class WriterVTK 
 *******************************************************************************
 *@brief     A Classe que gerencia escrita dos os arquivos de resultado.
 *@details   A Classe que gerencia escrita dos os arquivos de resultado. O      <!--
 *-->        arquivo do tipo VTK.  
 *******************************************************************************
 *@date      29/04/2021 - 29/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField> 
class WriterVTK : public VTK, public Writer{

private:
  ofstream fileOut;    /**< Arquivo de escrita*/
  IntTemp *intTemp;    /**< Objeto para integração temporal*/
  Mesh<TField>    *mesh;       /**< Objeto para a malha*/
  bool    firstCall;   /**< Guarda a primeira vez que o write é chamado*/

  string fullNameFile(void);

public:
  // ... Construtor
  /***************************************************************************
   *@brief Contrutor
   *@details Este construtor recebe referencias para mesh, inTemp         <!--
   *         , cellLoop e solver.
   ***************************************************************************
   *@param mesh     - Malha utilizada
   *@param intTemp  - Integração temporal
   *@param name     - o prefixo do arquivo de saida
   ***************************************************************************
   *@date      19/04/2021 - 25/04/2021
   *@author    Henrique C. C. de Andrade
   ***************************************************************************/
  WriterVTK(Mesh<TField>* mesh, IntTemp* intTemp, string name) {
    this->mesh = mesh;
    this->intTemp = intTemp;
    this->set_preName(name);
    this->firstCall = true;
  }

  /****************************************************************************
  * @brief Escreve os resultados.
  *****************************************************************************/
  void write(void) override;
  /****************************************************************************/

  /*****************************************************************************
  * @brief Fecha os arquivos de saida.
  ******************************************************************************
  * @date      19/04/2021 - 25/04/2021
  * @author    Henrique C. C. de Andrade
  ******************************************************************************/
  void closeOutputFile(void) override {
    fileOut.close();
  }

  /****************************************************************************
   *@brief     Abre os arquivos de saida
   ****************************************************************************/
  void openOutputFile(void) override;
  
  // ... getters
  /***************************************************************************
   * @brief Obtém a referencia do arquivo de saida para escrita
   ***************************************************************************
   * @return - referencia para o arquivo
   ***************************************************************************
   * @date      19/04/2021 - 25/04/2021
   * @author    Henrique C. C. de Andrade
   ***************************************************************************/
  ofstream& get_fileOut() { return this->fileOut; }
  
};

/*******************************************************************************
*@class Writers
*******************************************************************************
*@brief     A Classe que gerencia a escolhado do tipo do arquivos de saida.
*@details   A Classe que gerencia a escolhado do tipo do arquivos de saida.      
*           Escolhe entre os arquivos do tipo:                                      
*           TXT                                                                       
*           VTK
*******************************************************************************
*@date      19/04/2021 - 25/04/2021
*@author    Henrique C. C. de Andrade
***************************************************************************/
template <class TField> class Writers {

  public:
  /***************************************************************************
  *@details Seleciona a classe com o tipo de arquivo escolhido.
  ***************************************************************************
  *@param mesh     - Malha utilizada
  *@param intTemp  - Integração temporal
  *@param name     - O prefixo do arquivo de saida
  *@param cod      - Tipo do arquivo de saida
  ***************************************************************************
  *@date      2021 - 2021
  *@author    Henrique C. C. de Andrade
  ***************************************************************************/
    Writer* select(Mesh<TField>* mesh, IntTemp* intTemp, string name, int cod) {

      switch (cod){

      // ... Arquivo txt
        case typeWriters::typeTXT:
          return new WriterTxt<TField>(mesh, intTemp, name);
      
      // ... Arquivo VTK
        case typeWriters::typeVTK:
          return new WriterVTK<TField>(mesh, intTemp, name);

        default:
          cout<<"Tipo do arquivo de saida invalido!!" << endl;
          exit(typeOutFile);
      }
      return nullptr;
    };

};
// ............................................................................

#endif
