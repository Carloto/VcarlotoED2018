// Define
#ifndef REMAKE_TIPOESTAB_H
#define REMAKE_TIPOESTAB_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpTipo Tipo; // Tipo de estabelecimento

// Aloca e inicializa uma struct Tipo
Tipo *allocTipo();

// Libera a memoria de um unica Tipo
void killTipo(Tipo *tmpTipo);

// Deleta a Tipo
void deleteTipo(Tipo *tmpQuad);

// Retorna o tamanho de uma Tipo
size_t getTipoSize();

// Set codt
void setTipoCodt(Tipo *tmpTipo, char tmpCodt[25]);

// Set descricao
void setTipodDesc(Tipo *tmpTipo, char desc[50]);

// Get codt
char *getTipoCodt(Tipo *tmpTipo);

// Get descricao
char *getTipoDesc(Tipo *tmpTipo);

// Imprime as informações do Retangulo
void printTipo(Tipo *tmpTipo);

#endif // TIPOESTAB_H
