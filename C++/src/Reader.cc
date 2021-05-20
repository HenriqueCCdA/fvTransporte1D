#include"../include/Reader.h"

 /******************************************************************************
  *@brief     Leitura do arquivo de entrada
  *@details   Leitura do arquivo. Neste arquivo definido as caracteristica  <!--
  *-->        da simulação               
  ******************************************************************************
  *@date      2021 - 2021
  *@author    Henrique C. C. de Andrade
  *******************************************************************************/
template <class TField> 
void Reader<TField>::read(Mesh<TField> &mesh, IntTemp &intTemp,Files &files) {
  ifstream file;
  string name = files.get_nameIn();

  file.open(name, ios::in);
  if (!file.is_open()) {
    cout << name << " arquivo nao achado !" << endl;
    exit(error::fileNotFound);
  }

  string word;
  double dValue;
  int iValue;

  // ... loop de leitura
  while (file >> word) {

    transform(word.begin(), word.end(), word.begin(), ::tolower);

    // ... nome do arquivo de saida
    if (word == "output") {
      file >> word;
      files.set_prefixNameOut(word);
    }
    // ........................................................................

    // ... comprimento do dominio
    else if (word == "length") {
      file >> dValue;
      mesh.set_l(dValue);
    }
    // ........................................................................

    // ... numero de celulas
    else if (word == "ndiv") {
      file >> iValue;
      mesh.get_cells().set_nCells(iValue);
      mesh.get_nodes().set_nNodes(iValue + 1);
    }
    // ........................................................................

    // ... intervalo de tempo
    else if (word == "dt") {
      file >> dValue;
      intTemp.set_dt(dValue);
    }
    // ........................................................................

    // ... numero passos de tempo
    else if (word == "nstep") {
      file >> iValue;
      intTemp.set_nStep(iValue);
    }
    // ........................................................................

    // ... condicoes de contorno esquerdo
    else if (word == "cce") {
      int n = 0;
      double vValue[2];
      file >> iValue;
      mesh.get_ccci().set_cceType(iValue);
      if(iValue == typeCc::hConv){
        file >> vValue[0];
        file >> vValue[1];
        n = 2;
      }
      else {
        file >> vValue[0];
        n = 1;
      }
      mesh.get_ccci().set_cceValue(vValue, n);
    }
    // ........................................................................

    // ... condicoes de contorno direito
    else if (word == "ccd") {
      int n = 0;
      double vValue[2];
      file >> iValue;
      mesh.get_ccci().set_ccdType(iValue);

      if (iValue == typeCc::hConv) {
        file >> vValue[0];
        file >> vValue[1];
        n = 2;
      }
      else {
        file >> vValue[0];
        n = 1;
      }
      mesh.get_ccci().set_ccdValue(vValue, n);
    }
    // ........................................................................

    // ... condicao de contorno inicial
    else if (word == "initialu") {
      file >> dValue;
      mesh.get_ccci().set_cciValue(dValue);
    }
    // ........................................................................

    // ... leitura das propriedades
    else if (word == "rho" || word == "diffusion") {
      string type;

      cout << word << endl;

      file >> type;

      PropPhisicy *prop;
      if (word == "rho")
        prop = mesh.get_cells().get_prop().get_rho();
      else if(word == "diffusion")
        prop = mesh.get_cells().get_prop().get_coefDif();     

      // ... variaveis constantes
      if (type == "cte") {
        double vValue;
        file >> vValue;
        prop->set_type(typePropVar::cte);
        prop->set_valueCte(vValue);
      }

      // ... variacao por um polinomio
      else if (type == "pol") {
        double a[nTermPolMax];
        int iValue;
        file >> iValue;
      
        if (iValue > nTermPolMax) {
          cout << "Erro no numero de termos do poliniomo !!" << endl;
          exit(error::nTermsPol);
        }

        for (int i = 0; i < iValue; i++) {
          file >> a[i];
        }

        prop->set_type(typePropVar::varU);
        prop->get_pol()->set_a(a, iValue);
      }
      // ........................................................................     
    }
    // ........................................................................

    // ...
    else if (word == "end") break;
    // ........................................................................

  }
  // ........................................................................

  file.close();

  // ... alocando memoria
  mesh.alloc();
  // ........................................................................
}
/******************************************************************************/

// ...
template class Reader<FieldDif>;
// ............................................................................