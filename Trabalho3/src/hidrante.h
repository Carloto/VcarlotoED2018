#ifndef HIDRANTE__H
#define HIDRANTE__H

#include "misc.h"
#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Este módulo define as funções referentes aos hidrantes */

/* Struct que guarda as informações de um hidrante */
typedef struct hidrante{
  char *id;
  char *cor1;
  char *cor2;
  float x;
  float y;
  float raio;
} Hidrante;

/* Adiciona um novo hidrante*/
void new_hidrante(ListaGenerica **hid_head, ListaGenerica **hid_end, char *input_line, Cores* colors);

/* Free na struct e seus elementos */
void free_hidrante(ListaGenerica *temp_struct);

/* Imprimir o ultimo hidrante lido no svg */
void rthid_svg(FILE **OutputFile, ListaGenerica *HidFim);

/* Imprimir toda a lista de hidarantes na saida svg */
void phid_svg(FILE **OutputFile, ListaGenerica *lista_hidrante);

/* Função teste para imprimir lista */
void print_hidrante(ListaGenerica *lista_hidrante);

#endif
