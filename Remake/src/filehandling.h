// Define
#ifndef INPUTARGV_H
#define INPUTARGV_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
FILE *openFile(char *fileName, char accessType[6]);

// Imprime tags svg
void printTagSvg(FILE **outputFile, int type);

// Imprime um tipo de dado no arquivo binario
void printToBin(FILE **binFile, size_t dataSize, void *data);

// Lê um tipo de dado no arquivo binario
void readFromBin(FILE **binFile, size_t dataSize, void *data);

// Retorna o nome de do arquivo base
char *getInputGeoName(fileArguments *tmpStructs);

// Retorna o nome de do arquivo de entrada .geo
char *getInputGeoFileName(fileArguments *tmpStructs);

// Retorna o nome de do arquivo de entrada .qry
char *getInputQryFileName(fileArguments *tmpStructs);

// Retorna o nome de do arquivo de entrada .ec
char *getInputEcFileName(fileArguments *tmpStructs);

// Retorna o nome de do arquivo de entrada .pm
char *getInputPmFileName(fileArguments *tmpStructs);

// Retorna o nome de do arquivo de entrada .via
char *getInputViaFileName(fileArguments *tmpStructs);


// Retorna o nome de do arquivo de saida .svg do qry
char *getOutputQrySvgName(fileArguments *tmpStructs);

// Retorna o nome do arquivo de saida .svg padrão
char *getOutputSvgStandardFileName(fileArguments *tmpStructs);

// Retorna o nome do arquivo de saida .txt padrão
char *getOutputTxtFileName(fileArguments *tmpStructs);

// Retorna o nome base
char *getBaseName(fileArguments *tmpStructs);

// Retorna o output path
char *getOutputPath(fileArguments *tmpStructs);

// Retorna o diretorio do banco de dados
char *getFullPathBd(fileArguments *tmpStructs);


#endif //INPUTARGV_H
