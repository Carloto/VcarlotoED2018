// Define
#ifndef AUXFIG_H
#define AUXFIG_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct auxf AuxFigura; // Figuras auxiliares

// Aloca um no
AuxFigura *allocAux();

// Adiciona um no na cabeça
void addAux(AuxFigura **head, double x1, double y1, double x2, double y2, int tipo);

// Deleta a arvore
void killAux(AuxFigura **head);

// Imprime as figuras auxiliares no svg
void printAuxToSvg(AuxFigura *head, FILE **svgOutput);

#endif // AUXFIG_H
