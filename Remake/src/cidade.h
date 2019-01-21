// Define
#ifndef CIDADE_H
#define CIDADE_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include "miscfunctions.h"
#include "filehandling.h"
#include "quadra.h"
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

// Imprime as estruturas da cidade
void printCityShapes(Cidade *cityIndex);

#endif // CIDADE_H
