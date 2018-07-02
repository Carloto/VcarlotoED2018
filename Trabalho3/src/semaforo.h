#ifndef SEMAFORO__H
#define SEMAFORO__H

#include "misc.h"
#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Este módulo define as funções referentes aos semáforos */

/* Struct que guarda as informações de um semaforo  */
typedef struct semaforo{
  char *id;
  char *cor1;
  char *cor2;
  float x;
  float y;
  float width;
  float height;
} Semaforo;

/* Adiciona um novo semaforo*/
void new_semaforo(ListaGenerica **sem_head, ListaGenerica **sem_end, char *input_line, Cores* colors);

/* Free na struct e seus elementos */
void free_semaforo(ListaGenerica *temp_struct);

/* Imprimir o ultimo semaforo lido no svg */
void rtsem_svg(FILE **OutputFile, ListaGenerica *SemFim);

/* Função teste para imprimir lista */
void print_semaforo(ListaGenerica *lista_semaforo);

#endif
