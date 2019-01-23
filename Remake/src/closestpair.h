// Define
#ifndef CLOSESTPAIR_H
#define CLOSESTPAIR_H

typedef struct tmpPoint Point; // Coordenadas no plano

// Include
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

// Aloca um vetor de Point e retorna o ponteiro
Point *allocPoint(int n);

// Guarda informações no ponto
void infoToPoint(Point **P, int pos, unsigned long key, double x, double y);

// Encontra o par mais proximo e retorna a distancia
double closest(Point *P, int n, unsigned long *um, unsigned long *dois);

void printPoints(Point *P, int i);

void printClosestPoints(Point *P, int i);

#endif // CLOSESTPAIR_H
