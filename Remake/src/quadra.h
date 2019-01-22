// Define
#ifndef QUADRA_H
#define QUADRA_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpQuadra Quadra; // Quadra

// Aloca e inicializa uma struct Quadra
Quadra *allocQuadra();

// Libera a memoria de uma unica quadra
void killQuadra(Quadra *tmpQuad);

// Deleta a quadra
void deleteQuadra(Quadra *tmpQuad);

// Retorna o tamanho de uma quadra
size_t getQuadraSize();

// Set cep
void setQuadraCep(Quadra *tmpQuad, char tmpCep[50]);

// Set X
void setQuadraX(Quadra *tmpQuad, double tmpX);

// Set Y
void setQuadraY(Quadra *tmpQuad, double tmpY);

// Set width
void setQuadraWidth(Quadra *tmpQuad, double tmpWidth);

// Set height
void setQuadraHeight(Quadra *tmpQuad, double tmpHeight);

// Set fillColor
void setQuadraFillColor(Quadra *tmpQuad, char *tmpFillColor);

// Set strokeColor
void setQuadraStrokeColor(Quadra *tmpQuad, char *tmpStrokeColor);

// Get cep
char *getQuadraCep(Quadra *tmpQuad);

// Get X
double getQuadraX(Quadra *tmpQuad);

// Get Y
double getQuadraY(Quadra *tmpQuad);

// Get width
double getQuadraWidth(Quadra *tmpQuad);

// Get height
double getQuadraHeight(Quadra *tmpQuad);

// Get fillColor
char *getQuadraFillColor(Quadra *tmpQuad);

// Get strokeColor
char *getQuadraStrokeColor(Quadra *tmpQuad);

// Imprime as informações do Retangulo
void printQuadra(Quadra *tmpQuad);

#endif // QUADRA_H
