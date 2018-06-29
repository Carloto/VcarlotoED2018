#include "misc.h"

/* Imprime uma string não nula */
void print_this(char *output) {
  if (output != NULL) {
    printf("\n|%s|", output);
  }
}

/* Libera a string caso não seja nula, e aponta o ponteiro restante para NULL*/
void free_string(char **temp_free) {
  if (*temp_free != NULL) {
    free(*temp_free);
  }
  *temp_free = NULL;
}

/* Atualiza o valor do limite */
int update_lim(char *input_line) {
  char *token;
  int   ret;

  token = strtok(input_line, " ");
  token = strtok(NULL, " ");
  ret   = atoi(token);

  return ret;
}
