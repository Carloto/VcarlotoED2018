#ifndef PONTOS
#define PONTOS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linkedist.h"

typedef struct Ponto {
    float x;
    float y;
} ponto;

// Lida com funções referentes a contas algébricas entre pontos

void heapsort(ponto ponto[], int n);

void merge(ponto arr[], int l, int m, int r);

void mergeSort(ponto arr[], int l, int r);

void mergey(ponto arr[], int l, int m, int r);

void mergeSorty(ponto arr[], int l, int r);

float Distancia_Pontos(ponto pt1, ponto pt2);

float Menor_Float(float n1, float n2);

float Distancia_Minima(ponto *pt, int n);

float Menor_Front(ponto front[], int n, float mindist);

float Mais_Perto(ponto *pt, int n);

#endif
