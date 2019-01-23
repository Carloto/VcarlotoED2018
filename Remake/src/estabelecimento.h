// Define
#ifndef ESTABELECIMENTO_H
#define ESTABELECIMENTO_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpEstab Estab; // Estab

// Aloca e inicializa uma struct Estab
Estab *allocEstab();

// Libera a memoria de uma unica Estab
void killEstab(Estab *tmpEstab);

// Deleta a Estab
void deleteEstab(Estab *tmpEstab);

// Retorna o tamanho de uma Estab
size_t getEstabSize();

// Set cnpj
void setEstabCnpj(Estab *tmpEstab, char tmpCnpj[50]);

// Set codt
void setEstabCodt(Estab *tmpEstab, char tmpCodt[50]);

// Set cep
void setEstabCep(Estab *tmpEstab, char tmpCep[50]);

// Set face
void setEstabFace(Estab *tmpEstab, char tmpFace[2]);

// Set num
void setEstabNum(Estab *tmpEstab, int num);

// Set nome
void setEstabNome(Estab *tmpEstab, char tmpNome[50]);

// Set X
void setEstabX(Estab *tmpEstab, double tmpX);

// Set Y
void setEstabY(Estab *tmpEstab, double tmpY);

// Set fillColor
void setEstabFillColor(Estab *tmpEstab, char tmpFillColor[50]);

// Set strokeColor
void setEstabStrokeColor(Estab *tmpEstab, char tmpStrokeColor[50]);

// Get cnpj
char *getEstabCnpj(Estab *tmpEstab);

// Get codt
char *getEstabCodt(Estab *tmpEstab);

// Get cep
char *getEstabCep(Estab *tmpEstab);

// Get face
char *getEstabFace(Estab *tmpEstab);

// Get num
int getEstabNum(Estab *tmpEstab);

// Get cep
char *getEstabNome(Estab *tmpEstab);

// Get X
double getEstabX(Estab *tmpEstab);

// Get Y
double getEstabY(Estab *tmpEstab);

// Get fillColor
char *getEstabFillColor(Estab *tmpEstab);

// Get strokeColor
char *getEstabStrokeColor(Estab *tmpEstab);

// Imprime as informações do Retangulo
void printEstab(Estab*tmpEstab);

#endif // ESTABELECIMENTO_H
