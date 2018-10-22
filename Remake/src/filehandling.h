// Define
#ifndef TRAB3_INPUTARGV_H
#define TRAB3_INPUTARGV_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structlib.h"
#include "miscfunctions.h"

// O objetivo deste modulo é lidar com a entrada de argumentos na linha de comando

// Aloca espaço e inicializa as variaveis da struct input arguments
fileArguments *createInputArguments();

// Libera as strings e a struct input arguments
void killInputArguments(fileArguments **kill_struct);

// Imprime fileArguments
void printInputArguments(fileArguments *print_struct);

// Obtem os argumentos de argv
void setInputArguments(fileArguments **set_struct, int argc, char *argv[]);

// Lê uma linha do arquivo de entrada
void readLine(char **line, FILE **input);

// Abre um arquivo a partir do nome recebido
int openFile(char *fileName, char accessType[3], FILE **fileToOpen);

#endif //TRAB3_INPUTARGV_H
