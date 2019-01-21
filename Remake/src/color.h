// Define
#ifndef COLOR_H
#define COLOR_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"

typedef struct tmpColor Color; // Cores

// Aloca e inicializa uma struct Color
Color *allocColor();

// Libera a memoria de uma unica struct color
void killColor(Color *tmpCol);

// Adiciona uma nova cor a partir do arquivo lido
void newColorFromFile(Color *colorIndex, char *inputLine, int typeOfData);

// Get quadFill
char *getQuadFillColor(Color *tmpCol);

// Get quadStroke
char *getQuadStrokeColor(Color *tmpCol);

// Set quadFill
void setQuadFillColor(Color *tmpCol, char *aux);

// Set quadStroke
void setQuadStrokeColor(Color *tmpCol, char *aux);

#endif // COLOR_H
