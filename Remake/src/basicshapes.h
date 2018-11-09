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

#endif //BASICSHAPES_H
