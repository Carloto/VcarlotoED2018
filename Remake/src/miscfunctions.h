// Buffer maximo de leitura
#ifndef M_BUFFER
#define M_BUFFER 1000
#endif

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Esse modulo contem funções auxiliares para o programa

//Imprime uma string não nula
void printThis(char *output);

// Copia uma string
void copyString(char **final, char *aux);

// Libera uma string e aponta o ponteiro para null
void freeString(char **temp_free);

// Free double
void freeDouble(double **tmpValue);

// Free int
void freeInt(int **tmpValue) ;

// Remove o primeiro character da string
void removeFirstChar(char **final);

// Concatena nomes de arquivos, verificando a ausenica ou duplicata de "/"
void strcatFileName(char **final, char *before, char **after, char type[3]);

// Função de hashing para strings
unsigned long hash(unsigned char *str);

// Isola o nome de um arquivo
void cutFileName(char **final, char *aux);

// Conversão para inteiro
int newAtoi(char *aux);

// Conversão para double
double newAtod(char *aux);

// Retorna a distancia entre duas coordenadas
double findDistance(double aX, double aY, double bX, double bY);

// Verifica se um ponto é interno a  um circulo
int pointInsideCircle(double pointX, double pointY, double circleX, double circleY, double radius);

// Verifica se um ponto é interno a  um retangulo
int pointInsideRectangle(double pointX, double pointY, double rectX, double rectY, double width, double height);

#endif //MISCFUNCTIONS_H

// Resultados do hashing
#ifndef CMD_NX
#define CMD_NX 5863659
#endif

#ifndef CMD_O
#define CMD_O 177684
#endif

#ifndef CMD_I
#define CMD_I 177678
#endif

#ifndef CMD_D
#define CMD_D 177673
#endif

#ifndef CMD_A
#define CMD_A 177670
#endif

#ifndef CMD_FIM
#define CMD_FIM 177608
#endif

#ifndef FIG_C
#define FIG_C 177672
#endif

#ifndef FIG_R
#define FIG_R 177687
#endif
