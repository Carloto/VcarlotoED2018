// Define
#ifndef GRAFO_H
#define GRAFO_H

// Include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedist.h"
#include <math.h>
#include "ponto.h"

typedef struct tmpGraf { // Grafo
    List *verts;
    List *arestas;
} Grafo;

typedef struct tmpAresta { // Aresta
    char *src;
    char *dest;
    char *nome;
    char *ldir;
    char *lesq;
    float cmp;
    float vm;
} Aresta;

typedef struct tmpVert{
    int numericID;
    char *id;
    ponto Ponto;
    List *arestas;
} Vertice;

// Este modulo faz a manipulação de grafos

Grafo *Novo_Grafo();

void Coloca_Vertices(char *nome, int x, int y, Grafo *grafo, int numericID);

void Coloca_Aresta(char *src, char *dest, char *ldir, char *lesq, float cmp, float vm, char *nome, Grafo *grafo);

void Insere_Variaveis_Vertices(Grafo *grafo);

float **Insere_Var_Matriz(List *verts, float **matriz);

float **Insere_Distancias_Mat(List *verts, float **matriz);

int Aresta_Dentro_Vertices(Aresta *aresta, Vertice *vert);

Aresta *ArestaFinal(Vertice *vert1, Vertice *vert2);

#endif
