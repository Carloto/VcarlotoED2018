#ifndef REMAKE_CARRO_H
#define REMAKE_CARRO_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpCarro Carro;// Carro

// Aloca e inicializa uma struct Carro
Carro *allocCarro();

// Libera a memoria de uma unica Carro
void killCarro(Carro *tmpQuad);

// Deleta a Carro
void deleteCarro(Carro *tmpQuad);

// Retorna o tamanho de uma Carro
size_t getCarroSize();

// Set cep
void setCarroPlaca(Carro *tmpQuad, char tmpCep[25]);

// Set X
void setCarroX(Carro *tmpQuad, double tmpX);

// Set Y
void setCarroY(Carro *tmpQuad, double tmpY);

// Set width
void setCarroWidth(Carro *tmpQuad, double tmpWidth);

// Set height
void setCarroHeight(Carro *tmpQuad, double tmpHeight);

// Get cep
char *getCarroplaca(Carro *tmpQuad);

// Get X
double getCarroX(Carro *tmpQuad);

// Get Y
double getCarroY(Carro *tmpQuad);

// Get width
double getCarroWidth(Carro *tmpQuad);

// Get height
double getCarroHeight(Carro *tmpQuad);

#endif //REMAKE_CARRO_H
