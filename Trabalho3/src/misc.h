#ifndef MISC__H
#define MISC__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Este modulo contem funções diversas de contextos diferentes */

/* Lista ligada generica */
typedef struct lista {
  void *data;
  struct lista *next;
} ListaGenerica;

/* Lista para guardar as cores de preenchimento e borda */
typedef struct cores {
  char *quad_stroke;
  char *quad_fill;
  char *hid_stroke;
  char *hid_fill;
  char *tor_stroke;
  char *tor_fill;
  char *sem_stroke;
  char *sem_fill;
} Cores;

/* Imprime uma string não nula */
void print_this (char *output);

/* Libera a string caso não seja nula, e aponta o ponteiro restante para NULL*/
void free_string(char **temp_free);

/* Atualiza o valor do limite */
int update_lim (char *input_line);

/* Inicializa a struct de cores */
Cores *create_colors();

/* Destroi a struct de cores */
void destruir_colors(Cores *dc_kill);

/* Atualiza as cores de preenchimento e borda*/
Cores *get_colors(char *input_line, Cores* temp_colors);

#endif
