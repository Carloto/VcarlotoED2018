// Define
#ifndef HIDRANTE_H
#define HIDRANTE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpHidrante Hidrante; // Hidrante

// Aloca e inicializa uma struct Hidrante
Hidrante *allocHidrante();

// Libera a memoria de uma unica Hidrante
void killHidrante(Hidrante *tmpHid);

// Deleta o hidrante
void deleteHidrante(Hidrante *tmpHid);

// Retorna o tamanho de uma Hidrante
size_t getHidranteSize();

// Set id
void setHidranteId(Hidrante *tmpHid, char tmpId[50]);

// Set X
void setHidranteX(Hidrante *tmpHid, double tmpX);

// Set Y
void setHidranteY(Hidrante *tmpHid, double tmpY);

// Set radius
void setHidranteRadius(Hidrante *tmpHid, double tmpRadius);

// Set fillColor
void setHidranteFillColor(Hidrante *tmpHid, char *tmpFillColor);

// Set strokeColor
void setHidranteStrokeColor(Hidrante *tmpHid, char *tmpStrokeColor);

// Get Id
char *getHidranteId(Hidrante *tmpHid);

// Get X
double getHidranteX(Hidrante *tmpHid);

// Get Y
double getHidranteY(Hidrante *tmpHid);

// Get radius
double getHidranteRadius(Hidrante *tmpHid);

// Get fillColor
char *getHidranteFillColor(Hidrante *tmpHid);

// Get strokeColor
char *getHidranteStrokeColor(Hidrante *tmpHid);

// Imprime as informações do Hidrante
void printHidrante(Hidrante *tmpHid);

#endif // HIDRANTE_H
