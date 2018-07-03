#ifndef M_BUFFER
#define M_BUFFER 1000
#endif

#ifndef ARQUIVO__H
#define ARQUIVO__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "misc.h"
#include "geometricas.h"

/* Este modulo lida com a manipulação de arquvivos */

/* Lê uma linha do arquivo de entrada */
void get_linha(char *linha, FILE *entrada);

/* Esta struct guard os paths recebidos pelo argv */
typedef struct arq{
  char *output_path;
  char *input_path;
  char *input_name;
  char *input_qry;
} Arqs;

/* Retorna uma struct contendo os parametros recebidos por argv */
Arqs *ler_argv (int argc, char *argv[], Arqs *la_argv);

/* Inicializar Arqs */
Arqs *criar_arqs ();

/* Destruir Arqs */
void destruir_arqs (Arqs* da_kill);

/* Imprimir Arqs */
void print_arqs (Arqs *pa_arq);

/* Inicializar arquivo svg */
FILE *cria_svg (FILE *OutputFile, Arqs *temp_arq, char *after);

/* Fechar arquivo svg */
void destroi_svg (FILE **OutputFile);

/* Imprime a sobreposição */
void sbprint_svg(float x, float y, float width, float height, char *cor1, FILE **OutputFile);

/* Inicializar arquivo txt */
FILE *cria_txt (FILE *OutputFile, Arqs *temp_arq);

/* Fechar arquivo txt */
void destroi_txt (FILE **OutputFile);

/* Imprime a linha de resposta no txt de saida */
void rtprint_txt(FILE **OutputFile, char *resposta, char *linha, float distancia);

#endif
