// Define
#ifndef TRAB3_MISCFUNCTIONS_H
#define TRAB3_MISCFUNCTIONS_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esse modulo contem funções auxiliares para o programa

//Imprime uma string não nula
void print_this(char *output);

// Copia uma string
void copyString(char **final, char *aux);

// Libera uma string e aponta o ponteiro para null
void free_string(char **temp_free);

// Remove o primeiro character da string
void removeFirstChar(char **final);

// Concatena nomes de arquivos, verificando a ausenica ou duplicata de "/"
void strcatFileName(char **final, char *before, char **after);

#endif //TRAB3_MISCFUNCTIONS_H

