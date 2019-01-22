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

// Verificar validade da string
int checkString(char *aux);

//Imprime uma string não nula
void printThis(char *output);

// Copia uma string
void copyString(char **final, char *aux);

// Libera uma string e aponta o ponteiro para null
void freeString(char **temp_free);

// Free double
void freeDouble(double **tmpValue);

// Free int
void freeInt(int **tmpValue);

// Remove o primeiro character da string
void removeFirstChar(char **final);

// Concatena nomes de arquivos, verificando a ausenica ou duplicata de "/"
void strcatFileName(char **final, char *before, char **after, char type[50]);

// Concatena nomes
void strcatName(char **final, char *before, char **after, char type[50]);

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

// Verifica se dois circulos se sobrepoem
int
overlapCircleCircle(double aX, double aY, double aR, double bX, double bY, double bR, int controle, FILE **outputFile);

// Verifica se um circulo e um retangulo se sobrepoem
int
overlapCircleRectangle(double aX, double aY, double aR, double bX, double bY, double bWidth, double bHeight,
                       int controle, FILE **outputFile);

// Verifica se dois retangulos se sobrepoem
int
overlapRectangleRectangle(double aX, double aY, double aWidth, double aHeight, double bX, double bY, double bWidth,
                          double bHeight, int controle, FILE **outputFile);

// Verifica se um retangulo está dentro do outro
int
rectInsideRect(double aX, double aY, double aWidth, double aHeight, double bX, double bY, double bWidth,
               double bHeight);

// Imprime um retangulo tracejado
void printDashRectangle(FILE **outputFile, double rectX, double rectY, double width, double height);

// Imprime um retangulo tracejado com sobreposicao
void printOverlapRectangle(FILE **outputFile, double rectX, double rectY, double width, double height);

// Imprime um Circulo tracejado
void printDashCircle(FILE **outputFile, double cX, double cY, double radius);

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

#ifndef FIG_Q
#define FIG_Q 177686
#endif

#ifndef FIG_H
#define FIG_H 177677
#endif

#ifndef FIG_S
#define FIG_S 177688
#endif

#ifndef FIG_T
#define FIG_T 177689
#endif

#ifndef COR_Q
#define COR_Q 5863289
#endif

#ifndef COR_H
#define COR_H 5863280
#endif

#ifndef COR_S
#define COR_S 5863291
#endif

#ifndef COR_T
#define COR_T 5863292
#endif

#ifndef D_MIN_Q
#define D_MIN_Q 5863322
#endif

#ifndef D_MIN_LE
#define D_MIN_LE 193489562
#endif

#ifndef D_Q
#define D_Q 5862266
#endif

#ifndef D_LE
#define D_LE 193454714
#endif

#ifndef CC
#define CC  5863275
#endif

#ifndef CRD
#define CRD 6385126173
#endif

#ifndef CRB
#define CRB 6385126107
#endif

#ifndef Q_MIN_SEARCH
#define Q_MIN_SEARCH 5863701
#endif

#ifndef Q_SEARCH
#define Q_SEARCH 5862645
#endif
