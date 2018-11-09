// Define
#ifndef RECTANGLE_H
#define RECTANGLE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include "miscfunctions.h"
#include "genericlist.h"

typedef struct tmpRectangle Rectangle; // Retangulo

// Esse modulo contem as funções de manipulação de retangulos

// Aloca e inicializa uma struct Rectangle
Rectangle *allocRectangle();

// Libera a memoria de um unico retangulo
void killRectangle(Rectangle *tmpRect);

// Set type
void setRectangleType(Rectangle *tmpRect, int tmpType);

// Set number id
void setRectangleId(Rectangle *tmpRect, int tmpNumberId);

// Set X
void setRectangleX(Rectangle *tmpRect, double tmpX);

// Set Y
void setRectangleY(Rectangle *tmpRect, double tmpY);

// Set width
void setRectangleWidth(Rectangle *tmpRect, double tmpWidth);

// Set height
void setRectangleHeight(Rectangle *tmpRect, double tmpHeight);

// Set fillColor
void setRectangleFillColor(Rectangle *tmpRect, char *tmpFillColor);

// Set strokeColor
void setRectangleStrokeColor(Rectangle *tmpRect, char *tmpStrokeColor);

// Imprime as informações do circulo
void printRectangle(Rectangle *tmpRect);


#endif //RECTANGLE_H
