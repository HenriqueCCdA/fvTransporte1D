#ifndef ERROR_H
#define ERROR_H

/*******************************************************************************
 * @brief enumera��o que define os tipos de erro
 *******************************************************************************/
enum error {
  memory = -1, /**< Erro na aloca��o de memoria.*/  
  dimArraySize = -2, /**< Dimes�o do array invalida.*/
  fileNotFound = -3 /**< Arquivo n�o achado.*/
};


#endif