#ifndef MERGESORT__H
#define MERGESORT__H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "arquivo.h"
#include "geometricas.h"
#include "functions.h"
#include "quadra.h"
#include "semaforo.h"
#include "hidrante.h"
#include "torre.h"
#include "qryfunctions.h"

/* Inicializa as variaveis necessarias para o MergeSort */
void crb(FILE **OutputTxtStd, ListaGenerica** headRef, Circle **CircDash, Circle **CircDashFim);

/* Ordena a lista mudando para onde os nós apontam */
void MergeSort(ListaGenerica** headRef, float *d, Circle **CircDash, Circle **CircDashFim);

/* Verifica a distancia e mescla as listas */
ListaGenerica* SortedMerge(ListaGenerica* a, ListaGenerica* b, float *d, Circle **CircDash, Circle **CircDashFim);

/* Separa a lista em duas partes. */
void FrontBackSplit(ListaGenerica* source,
                    ListaGenerica** frontRef, ListaGenerica** backRef);

#endif
