#include"../include/Writer.h"

/***************************************************************************
 *@details Gera o nome do arquivo VTK                                       <!--
 *-->      a geometria. Apartir da segunda são escritos os resultados.
 ***************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
inline string WriterVTK::fullNameFile(void) {

  string number = to_string(this->intTemp->get_iStep());
  string name = this->get_preName() + "_" + number + ".vtk";

  return name;
  
}

/***************************************************************************
 *@details Escreve os resultados. A primeira vez que e chama é escrita      <!--
 *-->      a geometria. Apartir da segunda são escritos os resultados.
 ***************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
void WriterVTK::write(void) {

  ofstream& file = this->get_fileOut();

  this->openOutputFile();

  this->headVtk(file);

  this->timeVtk(file, 
                this->intTemp->get_iStep(),
                this->intTemp->get_t());

  this->coorVtk(file,                
                this->mesh->get_nodes().get_x(),
                this->mesh->get_nNodes(),
                1);

  this->cellsVtk(file,
                 this->mesh->get_cells().get_nodes(),
                 this->mesh->get_cells().get_nNodesByCell(),
                 this->mesh->get_cells().get_type(),
                 this->mesh->get_cells().get_nCells());


  this->closeOutputFile();
}
/****************************************************************************/

/******************************************************************************
 *@details   Abre os arquivos de saida para escrita dos resultados. <!--
 *-->        São abertos dois arquivos.
 ******************************************************************************
 *@date      18/04/2021 - 27/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
void WriterVTK::openOutputFile(void) {

  string name = this->fullNameFile();

  fileOut.open(name, ios::out);
  if (!fileOut.is_open()) {
    cout << name << " arquivo nao aberto !" << endl;
    exit(error::fileNotFound);
  }
  
}
/********************************************************************************/