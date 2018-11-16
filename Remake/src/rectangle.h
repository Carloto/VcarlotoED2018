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

// Get number id
int *getRectangleId(Rectangle *tmpRect);

// Get X
double *getRectangleX(Rectangle *tmpRect);

// Get Y
double *getRectangleY(Rectangle *tmpRect);

// Get width
double *getRectangleWidth(Rectangle *tmpRect);

// Get height
double *getRectangleHeight(Rectangle *tmpRect);

// Get fillColor
char *getRectangleFillColor(Rectangle *tmpRect);

// Get strokeColor
char *getRectangleStrokeColor(Rectangle *tmpRect);

// Imprime as informações do Retangulo
void printRectangle(Rectangle *tmpRect);


#endif //RECTANGLE_H
