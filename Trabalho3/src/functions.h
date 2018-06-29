#ifndef FUNCTIONS__H
#define FUNCTIONS__H

#include "geometricas.h"
#include "misc.h"
#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Este modulo contem a declaração e execução de funções a serem utilizadas */

/* Verifica a sobrepósição de figuras geometricas */
char *sobrepoe (Circle *Circulos, Rectangle *Retangulos, char *input_line, FILE **OutputFile);

/* Verifica se o ponto é intero à figura */
char *pto_int(Circle *Circulos, Rectangle *Retangulos, char *input_line);

/* Retorna a distancia entre 2 figuras */
float dist (Circle *Circulos, Rectangle *Retangulos, char *input_line);

/* Executa o comando a */
void cmd_a (Circle *Circulos, Rectangle *Retangulos, char *input_line, Arqs *Paths);

#endif
