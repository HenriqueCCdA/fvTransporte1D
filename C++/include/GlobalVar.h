#ifndef GLOBALVAR_H
#define  GLOBALVAR_H

#include"RunTimes.h"
#include"GerenciadoDeMemoria.h"

RunTimes times; /**< Objeto global com estrutura de tempos de cada fun��o */
Memoria mem;    /**< Objetoe global com estrutura de aloca��o de mem�ria */

int Memoria::countArrays = 0;
#endif
