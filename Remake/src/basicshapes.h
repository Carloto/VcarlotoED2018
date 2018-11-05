// Define
#ifndef CIRCLE_H
#define CIRCLE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"

typedef struct tmpCircle Circle; // Circulo
typedef struct tmpRectangle Rectangle; // Retangulo
typedef struct tmpBasicShapes BasicShapes; // Figuras basicas (circulo e retanulo)

// Esse modulo contem funcoes referentes a manipulacao de figuras basicas


// Aloca e inicializa uma struct BasicShapes
BasicShapes *allocBasicShapes();

// Aloca e inicializa uma struct Circle
Circle *allocCircle();

// Libera a memoria de toda a lista
void killBasicShapes(BasicShapes **tmpShapes);

// Libera a memoria de um unico circulo
void killCircle(Circle *tmpCircle);

// Imprime a lista de figuras basicas
void printBasicShapes(BasicShapes *tmpShapes);

// Imprime a lista de circulos
void printOneShapes(Circle *tmpShapes);

// Adiciona um novo circulo ao final da lista, a partir do arquivo lido
void newCircleFromFile(BasicShapes *shapesIndex, char *inputLine);

#endif //CIRCLE_H
