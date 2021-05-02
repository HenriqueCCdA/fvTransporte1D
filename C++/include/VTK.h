#ifndef VTK_H
#define VTK_H

#include<fstream>

#include"Mesh.h"


enum typeVTK {
  dotVTK   =  1, /**< Tipo ponto VTK*/
  lineVTK  =  3, /**< Tipo linha VTK*/
  triaVTK  =  5, /**< Tipo triangulo VTK*/
  quadVTK  =  9, /**< Tipo quadrilatero VTK*/
  tetraVTK = 10, /**< Tipo tetra VTK*/
  hexaVTK  = 12, /**< Tipo hexa VTK*/
  piraVTK  = 14  /**< Tipo piramede VTK*/
};

enum fieldVTK {
  scalarsVTK = 1,  /**< Tipo escalar*/
  vectorVTK  = 2,  /**< Tipo vetor*/
  tensor     = 3   /**< Tipo tensor*/
};

using namespace std;

class VTK {

  public:

    /***************************************************************************
    *@brief Escreve o cabecalho do arquivo vtk
    ***************************************************************************/
    void headVtk(ofstream &file, string s = "vtkFile");
  
    /***************************************************************************
    *@brief Informacao temporal do arquivo vtk
    ***************************************************************************/
    void timeVtk(ofstream &file, int const iStep, double const t);

    /***************************************************************************
    *@brief Escreve as coordenadas
    ***************************************************************************/
    void coorVtk(ofstream &file, double *x, int const nNodes, short const ndm);

    /***************************************************************************
    *@brief Escreve as coordenadas
    ***************************************************************************/
    void cellsVtk(ofstream &file, int *cells, short *nNodesByCell,
                 short *type,  int const nCells);

    /***************************************************************************
    *@bref Escreve propriedades 
    ***************************************************************************/   
    template<typename T> void propVtk(ofstream &file, T *p, string name,
                                     int const n, short const gdl,
                                     short const cod);

    /***************************************************************************
    *@details Inicia o campo de dados para celulas
    ***************************************************************************
    *@param file - Arquivo de escrita
    *@param nCells - Número de células
    ***************************************************************************
    *@date      01/05/2021 - 01/05/2021
    *@author    Henrique C. C. de Andrade
    ***************************************************************************/
    void cellData(ofstream &file, int const nCells) {
      file << endl << "CELL_DATA " <<  nCells << endl;
    }

    /***************************************************************************
    *@details Inicia o campo de dados para nodes   
    ***************************************************************************
    *@param file - Arquivo de escrita
    *@param nNodes - Número de nós
    ***************************************************************************
    *@date      01/05/2021 - 01/05/2021
    *@author    Henrique C. C. de Andrade
    ***************************************************************************/
    void pointData(ofstream &file, int const nNodes) {
      file << endl << "POINT_DATA " << nNodes << endl;
    }

};

/***************************************************************************
 *@details Escreve propriedades
 ***************************************************************************
 *@param file - Arquivo de escrita
 *@param cells - Conectividade nodal
 *@param nNodesByCell - Número de nós por célula
 *@param type - Tipo da célula
 *@param nCells - Número de células
 ***************************************************************************
 *@date      29/04/2021 - 29/04/2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
template<typename T> void VTK::propVtk(ofstream &file, T *p, string name,
                                       int const n, short const gdl,
                                       short const cod) {

  string type;

  if (typeid(T) == typeid(int))
    type = "int";
  else if (typeid(T) == typeid(double))
    type = "double";
  else {
    exit(error::vtk);
  }


  switch (cod) {
  case fieldVTK::scalarsVTK:
    file << endl;
    file << "SCALARS " << name << " " << type << " " << gdl << endl;
    file << "LOOKUP_TABLE default " << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < gdl; j++)
        file << p[i*gdl + j];
      file << endl;
    }


  }
};


#endif