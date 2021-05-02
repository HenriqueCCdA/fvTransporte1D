#ifndef READER_H
#define READER_H

#include"Mesh.h"
#include"IntTemp.h"
#include"Files.h"

/*******************************************************************************
 *@class Reader
 *******************************************************************************
 *@brief     A Classe que gerencia a leitura dos arquivos de entrada.
 *@details   A Classe que gerencia os arquivo e entrada.
 *******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Reader{

public:

  /***************************************************************************
  *@brief Leitura do dados iniciais.
  ***************************************************************************/
  void read(Mesh &mesh, IntTemp &intTemp, Files &files);
};


#endif
