#ifndef QUADRA__H
#define QUADRA__H

#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Este módulo define as funções referentes às quadras */

/* Struct que guarda as informações de uma quadra  */
typedef struct quadra {
  char *cep;
  char *cor1;
  char *cor2;
  float x;
  float y;
  float width;
  float height;
} Quadra;

/* Adiciona uma nova quadra */
void new_quadra(ListaGenerica **quad_head, ListaGenerica **quad_end, char *input_line, Cores* colors);

/* Free na struct e seus elementos */
void free_quadra(ListaGenerica *temp_struct);

/* Função teste para imprimir lista */
void print_quadra(ListaGenerica *lista_quadra);

#endif
