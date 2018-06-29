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
} Generic;

/* Imprime uma string não nula */
void print_this (char *output);

/* Libera a string caso não seja nula, e aponta o ponteiro restante para NULL*/
void free_string(char **temp_free);

/* Atualiza o valor do limite */
int update_lim (char *input_line);

#endif
