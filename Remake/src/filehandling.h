// Define
#ifndef INPUTARGV_H
#define INPUTARGV_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"

// Struct para guardar a entrada de argumentos
typedef struct tmp_fileArguments fileArguments;

// O objetivo deste modulo é lidar com a entrada de argumentos na linha de comando

// Aloca espaço e inicializa as variaveis da struct input arguments
fileArguments *createFileArguments();

// Libera as strings e a struct input arguments
void killFileArguments(fileArguments **kill_struct);

// Imprime fileArguments
void printInputArguments(fileArguments *print_struct);

// Obtem os argumentos de argv
void setFileArguments(fileArguments **set_struct, int argc, char **argv);

// Lê uma linha do arquivo de entrada
void readLine(char **line, FILE **input);

// Abre um arquivo a partir do nome recebido
FILE *openFile(fileArguments *tmpStruct, char accessType[3], int fileName);

#endif //INPUTARGV_H
