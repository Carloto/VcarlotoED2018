// Define
#ifndef SEMAFORO_H
#define SEMAFORO_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpSemaforo Semaforo; // Semaforo

// Aloca e inicializa uma struct Semaforo
Semaforo *allocSemaforo();

// Libera a memoria de uma unica Semaforo
void killSemaforo(Semaforo *tmpSemaf);

// Retorna o tamanho de uma Semaforo
size_t getSemaforoSize();

// Set id
void setSemaforoId(Semaforo *tmpSemaf, char tmpId[50]);

// Set X
void setSemaforoX(Semaforo *tmpSemaf, double tmpX);

// Set Y
void setSemaforoY(Semaforo *tmpSemaf, double tmpY);

// Set width
void setSemaforoWidth(Semaforo *tmpSemaf, double tmpWidth);

// Set height
void setSemaforoHeight(Semaforo *tmpSemaf, double tmpHeight);

// Set fillColor
void setSemaforoFillColor(Semaforo *tmpSemaf, char *tmpFillColor);

// Set strokeColor
void setSemaforoStrokeColor(Semaforo *tmpSemaf, char *tmpStrokeColor);

// Get id
char *getSemaforoId(Semaforo *tmpSemaf);

// Get X
double getSemaforoX(Semaforo *tmpSemaf);

// Get Y
double getSemaforoY(Semaforo *tmpSemaf);

// Get width
double getSemaforoWidth(Semaforo *tmpSemaf);

// Get height
double getSemaforoHeight(Semaforo *tmpSemaf);

// Get fillColor
char *getSemaforoFillColor(Semaforo *tmpSemaf);

// Get strokeColor
char *getSemaforoStrokeColor(Semaforo *tmpSemaf);

// Imprime as informações do Retangulo
void printSemaforo(Semaforo *tmpSemaf);

#endif // SEMAFORO_H
