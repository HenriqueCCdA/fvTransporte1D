#ifndef ERROR_H
#define ERROR_H

/*******************************************************************************
 * @brief enumeração que define os tipos de erro
 *******************************************************************************/
enum error {
  memory = -1, /**< Erro na alocação de memoria.*/  
  dimArraySize = -2, /**< Dimesão do array invalida.*/
  fileNotFound = -3, /**< Arquivo não achado.*/
  vtk          = -4, /**< Erro na escrita do VTK.*/
  typeOutFile  = -5, /**< Erro na escolha do tipo do arquivo de saida.*/
  nTermsPol    = -6  /**< Erro no numero de termos do poliniomo.*/
};


#endif