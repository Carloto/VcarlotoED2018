#ifndef QUADRA__H
#define QUADRA__H

#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Este módulo define as funções referentes às quadras */

/* Struct que guarda as informaçõesde uma quadra  */
typedef struct quadra {
  char *cep;
  float x;
  float y;
  float width;
  float height;
} Quadra;

#endif
