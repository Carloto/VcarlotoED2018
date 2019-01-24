// Define
#ifndef QUERY_H
#define QUERY_H

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
#include "cidade.h"

// Este modulo contem as chamadas para execução dos comandos qry

// Verifica quais estruturas se encontram totalmente dentro da area requisitada
void strucutreInsideRectangle(Cidade *cityIndex, char *linha, FILE **txtOutput, FILE **svgOutput, int action);

// Verifica quais estruturas se encontram totalmente dentro da area requisitada
void structureInsideCircle(Cidade *cityIndex, char *linha, FILE **txtOutput, FILE **svgOutput, int action);

// Modifica a cor de dada estrutura
void changeColor(Cidade *cityIndex, char *linha);

// Imprime os dados da estrutura requisitada
void reportStructure(Cidade *cityIndex, char *linha, FILE **txtOutput);

// Retorna o id da posicao
unsigned long returnPointKey(Point *P, int i);

// Encontra e reporta as radio-bases mais proximas
void closestTorres(Cidade *cityIndex, char *linha, FILE **txtOutput);

// m?
// Imprime os dados do morador requisitado pelo cep
void reportMorador(Cidade *cityIndex, char *linha, FILE **txtOutput, int action);

// mr?
// Imprime os dados dos moradores dentro da regiao
void reportMoradorRect(Cidade *cityIndex, char *linha, FILE **txtOutput);

#endif // QUERY_H
