#include"../include/Writer.h"

/***************************************************************************
 *@details Gera o nome do arquivo VTK                                       <!--
 *-->      a geometria. Apartir da segunda são escritos os resultados.
 ***************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
template <class TField> 
inline string WriterVTK<TField>::fullNameFile(void) {

  string number = to_string(this->intTemp->get_iStep());
  string name = this->get_preName() + "_" + number + ".vtk";

  return name;
  
}

/***************************************************************************
 *@details Escreve os resultados. A primeira vez que e chama é escrita      <!--
 *-->      a geometria. Apartir da segunda são escritos os resultados.
 ***************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
template <class TField>
void WriterVTK<TField>::write(void) {

  ofstream& file = this->get_fileOut();
  int nCells = this->mesh->get_cells().get_nCells();
  int nNodes = this->mesh->get_nodes().get_nNodes();

  // ... abrindo o arquivo
  this->openOutputFile();

  // ... cabecalho
  this->headVtk(file);

  this->timeVtk(file, 
                this->intTemp->get_iStep(),
                this->intTemp->get_t());
  
  // ... escrita das coordenadas
  this->coorVtk(file,                
                this->mesh->get_nodes().get_x(),
                this->mesh->get_nNodes(),
                1);
  // ... escrita dos elementos
  this->cellsVtk(file,
                 this->mesh->get_cells().get_nodes(),
                 this->mesh->get_cells().get_nNodesByCell(),
                 this->mesh->get_cells().get_type(),
                 nCells);
  
  // ... Campo por celulas
  this->cellData(file, nCells);

  this->propVtk<double>(file,
                this->mesh->get_cells().get_fields().get_u(),
                "cU",
                nCells,
                1,
                fieldVTK::scalarsVTK);

  this->propVtk<double>(file,
                this->mesh->get_cells().get_fields().get_gradU(),
                "cGradU",
                nCells,
                1,
                fieldVTK::scalarsVTK);

  this->propVtk<double>(file,
                        this->mesh->get_cells().get_fields().get_flux(),
                        "cFlux",
                        nCells,
                        1,
                        fieldVTK::scalarsVTK);

  // ... Campo por Pontos
  this->pointData(file, nNodes);

  this->propVtk<double>(file,
                      this->mesh->get_nodes().get_fields().get_u(),
                      "nU",
                      nNodes,
                      1,
                      fieldVTK::scalarsVTK);

  this->propVtk<double>(file,
                        this->mesh->get_nodes().get_fields().get_gradU(),
                        "nGradU",
                         nNodes,
                         1,
                         fieldVTK::scalarsVTK);

  this->propVtk<double>(file,
                        this->mesh->get_nodes().get_fields().get_flux(),
                        "nFlux",
                        nNodes,
                        1,
                        fieldVTK::scalarsVTK);

  // ... fechando o arquivo
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
template <class TField>
void WriterVTK<TField>::openOutputFile(void) {

  string name = this->fullNameFile();

  fileOut.open(name, ios::out);
  if (!fileOut.is_open()) {
    cout << name << " arquivo nao aberto !" << endl;
    exit(error::fileNotFound);
  }
  
}
/********************************************************************************/

// ...
template class WriterVTK<FieldDif>;
// ...........................................................................