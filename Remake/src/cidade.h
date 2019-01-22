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

typedef struct tmpCidade Cidade; // Estruturas da cidade

// Este modulo implementa a manipulação das estruturas presentes na cidade, como equipamentos urbanos e quadras, alem da execução de funções

// Aloca e inicializa uma struct Cidade
Cidade *allocCidade(fileArguments *source);

// Libera a memoria de toda a Cidade
void killCidade(Cidade **tmpBitnopolis);

// Adiciona uma nova estrutura no arquivo binario e na b-tree, a partir do arquivo lido
void newCityShapeFromFile(Cidade *cityIndex, char *inputLine, Color *colorIndex, int typeOfData);

// Verifica quais quadras estão dentro de dado retangulo
void quadraInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                           double aHeigth);

// Verifica quais semaforos estão dentro de dado retangulo
void semafInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                          double aHeigth);

// Verifica quais hidrantes estão dentro de dado retangulo
void hidInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                        double aHeigth);

// Verifica quais semaforos estão dentro de dado retangulo
void torreInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                          double aHeigth);

// Imprime as estruturas da cidade
void printCityShapes(Cidade *cityIndex);

// Imprime a lista de estruturas da cidade no arquivo de saida .svg
void printCityShapesToSvg(Cidade *cityIndex, FILE **outputFile);

#endif // CIDADE_H
