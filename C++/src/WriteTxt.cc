#include"../include/Writer.h"

static void writeResLine(ofstream &file, int c1, double c2, double *cs, int nCs);

/***************************************************************************
 *@details Escreve os resultados. A primeira vez que e chama é escrita      <!--
 *-->      a geometria. Apartir da segunda são escritos os resultados.
 ***************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
template <class TField>
void WriterTxt<TField>::write(void){

  // ... geometria
  if (this->firstCall) {
    this->openOutputFile();
    this->geomCell(*this->mesh);
    this->geomNode(*this->mesh);
    this->firstCall = false;
  }
  // ... resultados
  else {
    this->resCell(*this->mesh, *this->intTemp);
    this->resNode(*this->mesh, *this->intTemp);
  }
}
/****************************************************************************/

/******************************************************************************
 *@details Escreve os resultado nodais.
 ******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
template <class TField>
void WriterTxt<TField>::resNode(Mesh<TField> &Mesh, IntTemp &intTemp) {
  double *u = mesh->get_nodes().get_fields()->get_u();
  writeResLine(this->fileOutNode, intTemp.get_iStep(), intTemp.get_t(),
               u, Mesh.get_nNodes());

}
/******************************************************************************/

/******************************************************************************
 *@details Escreve coordenada dos nós.
 ******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
template <class TField>
void WriterTxt<TField>::geomNode(Mesh<TField> &mesh) {

  writeResLine(this->fileOutNode, 0, 0.0, mesh.get_nodes().get_x()
    , mesh.get_nNodes());

}
/**********************************************************************/

/******************************************************************************
 *@details  Escreve os resultado por células.
 ******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
template <class TField>
void WriterTxt<TField>::resCell(Mesh<TField> &mesh, IntTemp &intTemp) {

  double *u = mesh.get_cells().get_fields()->get_u();

  writeResLine(this->fileOutCell, intTemp.get_iStep(), intTemp.get_t(),
               u, mesh.get_nCells());

}
/******************************************************************************/

/******************************************************************************
 *@details Escreve as coordenada dos centraiodes.
 ******************************************************************************
 *@date      2021 - 2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
template <class TField>
void WriterTxt<TField>::geomCell(Mesh<TField> &mesh) {

  writeResLine(this->fileOutCell, 0, 0.0, mesh.get_cells().get_xc()
    , mesh.get_nCells());

}
/******************************************************************************/

/******************************************************************************
 *@details   Abre os arquivos de saida para escrita dos resultados. <!--
 *-->        São abertos dois arquivos.
 ******************************************************************************
 *@date      18/04/2021 - 27/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
template <class TField>
void WriterTxt<TField>::openOutputFile(void) {

  string name = this->get_preName() + "_node.c++";

  this->nameOutNode = name;

  fileOutNode.open(name, ios::out);
  if (!fileOutNode.is_open()) {
    cout << name << " arquivo nao aberto !" << endl;
    exit(error::fileNotFound);
  }

  name = this->get_preName() + "_cell.c++";

  this->nameOutCell = name;

  fileOutCell.open(name, ios::out);
  if (!fileOutNode.is_open()) {
    cout << name << " arquivo nao aberto !" << endl;
    exit(error::fileNotFound);
  }
}
/********************************************************************************/


static void writeResLine(ofstream &file, int c1, double c2, double *cs, int nCs) {

  file << setw(8) << c1 << " "
    << fixed << setw(12) << setprecision(4) << c2;

  for (int i = 0; i < nCs; i++) {
    file << " " << setprecision(7) << scientific << cs[i];
  }
  file << endl;
}

// ...
template class WriterTxt<FieldDif>;
// ............................................................................