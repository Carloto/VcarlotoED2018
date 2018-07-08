#ifndef QRYFUNCTIONS__H
#define QRYFUNCTIONS__H

#include "misc.h"
#include "arquivo.h"
#include "semaforo.h"
#include "hidrante.h"
#include "torre.h"
#include "quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Muda a cor de uma figura dado um id/cep */
void change_color(FILE** OutputFile, ListaGenerica *Hidrantes, ListaGenerica *Torres, ListaGenerica *Semaforos, ListaGenerica *Quadras, char *input_line);

/* Reporta as informaçoes de uma figura dado um id/cep */
void report_id(FILE         **OutputTxtStd,
               ListaGenerica *Hidrantes,
               ListaGenerica *Torres,
               ListaGenerica *Semaforos,
               ListaGenerica *Quadras,
               char          *input_line);

/* Executa o comando q? */
void interno_retangulo(FILE **OutputFile, FILE **OutputTxtStd, ListaGenerica *Hidrantes, ListaGenerica *Torres, ListaGenerica *Semaforos, ListaGenerica *Quadras, char *input_line);

/* Executa o comando Q? */
void interno_circulo(FILE **OutputFile, FILE **OutputTxtStd, ListaGenerica *Hidrantes, ListaGenerica *Torres, ListaGenerica *Semaforos, ListaGenerica *Quadras, char *input_line);

/* Executa a destruição de figuras dentro de retangulos e circulos */
void kill_inside(FILE          **OutputFile,
                 FILE          **OutputTxtStd,
                 ListaGenerica  **Hidrantes,
                 ListaGenerica  **Torres,
                 ListaGenerica  **Semaforos,
                 ListaGenerica **Quadras,
                 char           *input_line) ;

#endif
