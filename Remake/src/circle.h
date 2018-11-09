// Define
#ifndef CIRCLE_H
#define CIRCLE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include "miscfunctions.h"
#include "genericlist.h"

typedef struct tmpCircle Circle; // Circulo

// Esse modulo contem as funções de manipulação de círculos

// Aloca e inicializa uma struct Circle
Circle *allocCircle();

// Libera a memoria de um unico circulo
void killCircle(Circle *tmpCircle);

// Set type
void setCircleType(Circle *tmpCircle, int tmpType);

// Set number id
void setCircleId(Circle *tmpCircle, int tmpNumberId);

// Set radius
void setCircleRadius(Circle *tmpCircle, double tmpRadius);

// Set xCenter
void setCircleX(Circle *tmpCircle, double tmpXCenter);

// Set yCenter
void setCircleY(Circle *tmpCircle, double tmpYCenter);

// Set fillColor
void setCircleFillColor(Circle *tmpCircle, char *tmpFillColor);

// Set strokeColor
void setCircleStrokeColor(Circle *tmpCircle, char *tmpStrokeColor);

// Imprime as informações do circulo
void printCircle(Circle *tmpCircle);

#endif //CIRCLE_H
