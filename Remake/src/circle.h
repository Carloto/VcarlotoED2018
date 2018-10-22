// Define
#ifndef TRAB3_CIRCLE_H
#define TRAB3_CIRCLE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "structlib.h"

// Esse modulo contem funcoes referentes a manipulacao de circulos

// Aloca e inicializa uma struct Circle
Circle *allocCircle();

// Libera a memoria da lista ligada de circulos
void killCircle(genericList *tmpStruct);

// Imprime a lista de circulos
void printAllCircles(genericList *tmpCircles);

#endif //TRAB3_CIRCLE_H
