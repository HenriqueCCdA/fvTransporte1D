#ifndef VTK_H
#define VTK_H

#include<ostream>

enum typeVTK {
  dotVTK   =  1, /**< Tipo ponto VTK*/
  lineVTK  =  3, /**< Tipo linha VTK*/
  triaVTK  =  5, /**< Tipo triangulo VTK*/
  quadVTK  =  9, /**< Tipo quadrilatero VTK*/
  tetraVTK = 10, /**< Tipo tetra VTK*/
  hexaVTK  = 12, /**< Tipo hexa VTK*/
  piraVTK  = 14  /**< Tipo piramede VTK*/
};

using namespace std;

class VTK {

  public:

    /***************************************************************************
    *@details Escreve o cabecalho do arquivo vtk
    ***************************************************************************
    *@param file - Arquivo de escrita
    *@s     s - String do cabecalho do arquivo
    ***************************************************************************
    *@date      29/04/2021 - 29/04/2021
    *@author    Henrique C. C. de Andrade
    ***************************************************************************/
    void headVtk(ofstream &file, string s = "vtkFile"){
   
      file << "# vtk DataFile Version 3.0" << endl;
      file << s << endl;
      file << "ASCII" << endl;
      file << "DATASET UNSTRUCTURED_GRID" << endl;
      
    };

    /***************************************************************************
    *@details Informacao temporal do arquivo vtk
    ***************************************************************************
    *@param file - Arquivo de escrita
    *@param iStep - Passo de tempo
    *@param t    - Tempo                  
    ***************************************************************************
    *@date      29/04/2021 - 29/04/2021
    *@author    Henrique C. C. de Andrade
    ***************************************************************************/
    void timeVtk(ofstream &file, int const iStep, double const t) {

      file << "FIELD FieldData 3" << endl;

      //... passo de tempo
      file << "CYCLE 1 1 int" << endl;
      file << iStep << endl;

      //... tempo em segundos
      file << "TIME_S 1 1 double" << endl;
      file << t << endl;

      //... tempo em horas
      file << "TIME_H 1 1 double" << endl;
      file << t/3600.e0 << endl;

    };

    /***************************************************************************
    *@details Escreve as coordenadas
    ***************************************************************************
    ***************************************************************************
    *@param file - Arquivo de escrita
    ***************************************************************************
    *@date      29/04/2021 - 29/04/2021
    *@author    Henrique C. C. de Andrade
    ***************************************************************************/
    void coorVtk(ofstream &file, double *x, int const nNodes, short const ndm) {
   
      file << "POINTS " << nNodes << " double" << endl;
      
      if (ndm == 1) {
        for (int i = 0; i < nNodes; i++) {
          file << setprecision(7) << scientific << x[i] << " "
               << setprecision(7) << scientific << 0.0 << " "
               << setprecision(7) << scientific << 0.0 << " "
               << endl; 
        }         
      }
    
    };

    /***************************************************************************
    *@details Escreve as coordenadas
    ***************************************************************************
    ***************************************************************************
    *@param file - Arquivo de escrita
    ***************************************************************************
    *@date      29/04/2021 - 29/04/2021
    *@author    Henrique C. C. de Andrade
    ***************************************************************************/
    void cellsVtk(ofstream &file, int *cells, short *nNodesByCell,
                 short *type,  int const nCells) {

      unsigned long aux = 0;

      for (int i = 0; i < nCells; i++) {
        aux += nNodesByCell[i] + 1;
      }
      
      // ...
      file << "CELLS " << nCells << " " << aux << endl;
      for (int i = 0; i < nCells; i++) {
        short nbc =nNodesByCell[i];
        file << nbc << " ";
        for(int j = 0; j < nbc; j ++){
           int k = nbc*i + j;
           file << cells[k] << " ";
        }
        file << endl;   
      }
      // ......................................................................

      // ...
      file << endl;
      file << "CELL_TYPES " << nCells<< endl;
      for (int i = 0; i < nCells; i++) {
        short cod;
        if(type[i] == typeCell::line)
          cod = typeVTK::lineVTK;
        file << cod << endl;;
      }
      // ......................................................................

    };

};


#endif