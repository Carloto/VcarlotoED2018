#ifndef GEOMETRICAS__H
#define GEOMETRICAS__H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"

/* Este modulo inclui listas e operações relacionas às formas geometricas necessárias */

/*###################################################*/

/* Guarda as informações para a criação de um circulo */
typedef struct circ {
  int id;
  char *cor1;
  char *cor2;
  float raio;
  float x;
  float y;
  struct circ *next;
} Circle;

/* Função teste para imprimir lista */
void print_circle (Circle *temp_circ);

/* Aloca espaço para um nó */
Circle *create_cnode (Circle *temp_struct);

/* Adiciona um nó na lista de circulos dash */
void new_dash_node(Circle **temp_struct, Circle **temp_end, float x, float y, float raio);

/* Free na struct e seus elementos */
void free_cstruct(Circle* temp_struct);

/* Adiciona um nó na lista de circulos */
void new_cnode (Circle **temp_struct, Circle **temp_end, char *input_line);

/* Encontra a figura dado um id */
int find_id_circle(Circle **cnode, Circle *Circulos, int id);

/*###################################################*/

/* Guarda as informações para a criação de um retangulo */
typedef struct rect {
  int id;
  char *cor1;
  char *cor2;
  float width;
  float height;
  float x;
  float y;
  struct rect *next;
} Rectangle;

/* Função teste para imprimir lista */
void print_rect (Rectangle *temp_circ);

/* Aloca espaço para um nó */
Rectangle *create_rnode (Rectangle *temp_struct);

/* Free na struct e seus elementos */
void free_rstruct(Rectangle* temp_struct);

/* Adiciona um nó na lista de retangulos */
void new_rnode (Rectangle **temp_struct, Rectangle **temp_end, char *input_line);

/* Encontra a figura dado um id */
int find_id_rect(Rectangle **rnode, Rectangle *Retangulos, int id);

/* Imprime a figura geometrica no arquivo de saida */
void rtprint_svg (FILE **OutputFile, Circle *rs_circ, Rectangle *rs_rect);

/* Imprimir as figuras */
void print_geometricas(FILE **OutputFile, Circle *Circulos,
                       Rectangle *Retangulos);

#endif
