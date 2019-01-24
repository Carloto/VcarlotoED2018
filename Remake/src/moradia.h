// Define
#ifndef MORADIA_H
#define MORADIA_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpMora Moradia; // Moradia

// Aloca e inicializa uma struct Moradia
Moradia *allocMoradia();

// Libera a memoria de um unica Moradia
void killMoradia(Moradia *tmpMoradia);

// Deleta a Moradia
void deleteMoradia(Moradia *tmpMoradia);

// Retorna o tamanho de uma Moradia
size_t getMoradiaSize();

// Set cpf
void setMoradiaCpf(Moradia *tmpMoradia, char tmpCpf[25]);

// Set cep
void setMoradiaCep(Moradia *tmpMoradia, char tmpCep[50]);

// Set face
void setMoradiaFace(Moradia *tmpMoradia, char tmpFace[2]);

// Set num
void setMoradiaNum(Moradia *tmpMoradia, int tmpNum);

// Set complemento
void setMoradiaComplemento(Moradia *tmpMoradia, char tmpCompl[50]);

// Get cpf
char *getMoradiaCpf(Moradia *tmpMoradia);

// Get cep
char *getMoradiaCep(Moradia *tmpMoradia);

// Get face
char *getMoradiaFace(Moradia *tmpMoradia);

// get num
int getMoradiaNum(Moradia *tmpMoradia);

// Get complemento
char *getMoradiaComplemento(Moradia *tmpMoradia);

// Imprime as informações do Retangulo
void printMoradia(Moradia *tmpMoradia);

#endif // MORADIA_H
