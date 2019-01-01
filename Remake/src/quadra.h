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

// Esse módulo contém as funções de manipulação de quadras

// Adiciona uma nova quadra
void newQuadra( char *inputLine, FILE **binFile);

// Print quadras
void printBinQuadra(FILE **binFile);

#endif // QUADRA_H
