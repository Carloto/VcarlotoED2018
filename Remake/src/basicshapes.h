// Define
#ifndef BASICSHAPES_H
#define BASICSHAPES_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "genericlist.h"
#include "circle.h"
#include "rectangle.h"
#include "filehandling.h"

typedef struct tmpBasicShapes BasicShapes; // Figuras basicas (circulo e retanulo)

// Esse modulo contem funcoes referentes a manipulacao de figuras basicas

// Aloca e inicializa uma struct BasicShapes
BasicShapes *allocBasicShapes();

// Libera a memoria de toda a lista
void killBasicShapes(BasicShapes **tmpShapes);

// Imprime a lista de figuras basicas
void printBasicShapes(BasicShapes *tmpShapes);

// Adiciona uma nova figura ao final da lista, a partir do arquivo lido
void newShapeFromFile(BasicShapes *shapesIndex, char *inputLine, int typeOfData);

// Imprime a lista de figuras no arquivo de saida .svg
void printBasicShapesToSvg(BasicShapes *shapesIndex, FILE **outputFile);

// Encontra uma figura na lista a partir de um id
int searchBasicShapesId(BasicShapes *tmpShapes, genericList **tmpNode, int id);

// Verifica se um ponto é interno a uma figura
void insideBasicShapes(BasicShapes *tmpShapes, char *inputLine, FILE **outputFile);

// Calcula a distancia entre duas figuras basicas
void distanceBasicShapes(BasicShapes *tmpShapes, char *inputLine, FILE **outputFile);

// Verifica a sobreposicao fe  duas figuras basicas
void overlapBasicShapes(BasicShapes *tmpShapes, char *inputLine, FILE **outputTxt, FILE **outputSvg);

// Traça linhas a partir do id
void linesFromId(BasicShapes *tmpShapes, char *inputLine, fileArguments *tmpFileNames);

#endif //BASICSHAPES_H
