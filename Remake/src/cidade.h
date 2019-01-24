// Define
#ifndef CIDADE_H
#define CIDADE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include "miscfunctions.h"
#include "filehandling.h"
#include "quadra.h"
#include "torre.h"
#include "semaforo.h"
#include "hidrante.h"
#include "btree.h"
#include "color.h"
#include "closestpair.h"
#include "estabelecimento.h"
#include "tipoestab.h"
#include "pessoa.h"
#include "moradia.h"
#include "auxfig.h"

typedef struct tmpCidade Cidade; // Estruturas da cidade

// Este modulo implementa a manipulação das estruturas presentes na cidade, como equipamentos urbanos e quadras, alem da execução de funções

// Aloca e inicializa uma struct Cidade
Cidade *allocCidade(fileArguments *source);

// Libera a memoria de toda a Cidade
void killCidade(Cidade **tmpBitnopolis);

// Adiciona uma nova estrutura no arquivo binario e na b-tree, a partir do arquivo lido
void newCityShapeFromFile(Cidade *cityIndex, char *inputLine, Color *colorIndex, int typeOfData);

// Retorna um ponteiro para o arquivo requisitado
FILE **getCityFile(Cidade *cityIndex, int action);

// Cria um vetor de pontos de certa estrutura
Point *torreToPoint(Cidade *cityIndex);

// Declara uma pessoa morta e deleta suas informações
void ripPessoa(Cidade *cityIndex, unsigned long id);

// Adiciona uma figura auxiliar a partir da quadra
void addAuxQuadra(Quadra *tmpQuad, AuxFigura **tmpAux, int num, int face,int type);

// Imprime a pessoa e a moradia para o txt
void pessoaMoradiaTxt(Moradia *tmpMoradia, Pessoa *tmpPessoa, Quadra *tmpQuadra, FILE **txtOutput, int action);

// Imprime o estabelecimento e a quadra para o txt
void estabQuadraTxt(Estab *tmpEstab, Tipo *tmpTipo, Quadra *tmpQuad, FILE **txtOutput, int action);

// Retorna o numero de torres
int getNumTorres(Cidade *cityIndex);

// Retorna 1 e modifica address caso encontre a estrutura
int getQuadraAddress(Cidade *cityIndex, unsigned long id, long int *address, Quadra **aux);

// Retorna 1 e modifica address caso encontre a estrutura
int getMoradiaAddress(Cidade *cityIndex, unsigned long id, long int *address, Moradia **aux, int action);

// Retorna 1 e modifica address caso encontre a estrutura
int getPessoaAddress(Cidade *cityIndex, unsigned long id, long int *address, Pessoa **aux);

// Retorna 1 e modifica address caso encontre a estrutura
int getEstabAddress(Cidade *cityIndex, unsigned long id, long int *address, Estab **aux);

// Retorna 1 e modifica address caso encontre a estrutura
int getTipoAddress(Cidade *cityIndex, unsigned long id, long int *address, Tipo **aux);

// Retorna 1 e modifica address caso encontre a estrutura
int getSemaforoAddress(Cidade *cityIndex, unsigned long id, long int *address, Semaforo **aux);

// Retorna 1 e modifica address caso encontre a estrutura
int getHidranteAddress(Cidade *cityIndex, unsigned long id, long int *address, Hidrante **aux);

// Retorna 1 e modifica address caso encontre a estrutura
int getTorreAddress(Cidade *cityIndex, unsigned long id, long int *address, Torre **aux);

// Verifica quais quadras estão dentro de dado retangulo
void quadraInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                           double aWidth,
                           double aHeigth, int action);

// Verifica quais quadras estão dentro de dado circulo
void quadraInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                        double radius,
                        int action);

// Verifica quais semaforos estão dentro de dado retangulo
void semafInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                          double aWidth,
                          double aHeigth, int action);

// Verifica quais semaforos estão dentro de dado circulo
void semafInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                       double radius,
                       int action);

// Verifica quais hidrantes estão dentro de dado retangulo
void hidInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                        double aWidth,
                        double aHeigth, int action);

// Verifica quais hidrantes estão dentro de dado circulo
void hidInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double radius,
                     int action);

// Verifica quais torres estão dentro de dado retangulo
void torreInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                          double aWidth,
                          double aHeigth, int action);

// Verifica quais torres estão dentro de dado circulo
void torreInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY,
                       double radius,
                       int action);

// Imprime as estruturas da cidade
void printCityShapes(Cidade *cityIndex);

// Imprime a lista de estruturas da cidade no arquivo de saida .svg
void printCityShapesToSvg(Cidade *cityIndex, FILE **outputFile);

#endif // CIDADE_H
