// Define
#ifndef TORRE_H
#define TORRE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpTorre Torre; // Torre

// Aloca e inicializa uma struct Torre
Torre *allocTorre();

// Libera a memoria de uma unica Torre
void killTorre(Torre *tmpTor);

// Retorna o tamanho de uma Torre
size_t getTorreSize();

// Set id
void setTorreId(Torre *tmpTor, char tmpId[50]);

// Set X
void setTorreX(Torre *tmpTor, double tmpX);

// Set Y
void setTorreY(Torre *tmpTor, double tmpY);

// Set Radius
void setTorreRadius(Torre *tmpTor, double tmpRadius);

// Set fillColor
void setTorreFillColor(Torre *tmpTor, char *tmpFillColor);

// Set strokeColor
void setTorreStrokeColor(Torre *tmpTor, char *tmpStrokeColor);
// Get Id
char *getTorreId(Torre *tmpTor);

// Get X
double getTorreX(Torre *tmpTor);

// Get Y
double getTorreY(Torre *tmpTor);

// Get Radius
double getTorreRadius(Torre *tmpTor);

// Get fillColor
char *getTorreFillColor(Torre *tmpTor);

// Get strokeColor
char *getTorreStrokeColor(Torre *tmpTor);

// Imprime as informações da Torre
void printTorre(Torre *tmpTor);

#endif // TORRE_H
