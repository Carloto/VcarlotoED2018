#ifndef TORRE__H
#define TORRE__H

#include "misc.h"
#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Este módulo define as funções referentes às torres */

/* Struct que guarda as informações de uma torre */
typedef struct torre{
  char *id;
  char *cor1;
  char *cor2;
  float x;
  float y;
  float raio;
} Torre;

/* Adiciona uma nova torre */
void new_torre(ListaGenerica **tor_head, ListaGenerica **tor_end, char *input_line, Cores* colors);

/* Free na struct e seus elementos */
void free_torre(ListaGenerica *temp_struct);

/* Imprimir a ultima torre lida no svg */
void rttor_svg(FILE **OutputFile, ListaGenerica *TorFim);

/* Imprimir toda a lista de torres na saida svg */
void ptor_svg(FILE **OutputFile, ListaGenerica *lista_torre);

/* Encontra a figura dado um id */
int find_id_torre(ListaGenerica **tor_node, ListaGenerica *Torres, char *id);

/* Função teste para imprimir lista */
void print_torre(ListaGenerica *lista_torre);

#endif
