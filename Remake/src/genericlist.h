// Define
#ifndef GENERICLIST_H
#define GENERICLIST_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"

// Lista ligada generica
typedef struct tmp_genericList genericList;

// Esse módulo implementa as funções referentes a lista generica

// Adiciona um tipo de dado ao ponteiro data
void setNewData(genericList *tmpStruct, void *data, int type);

// Adciona um novo nó no inicio ou no final da lista
void addNewNode(genericList **tmpHead, genericList **tmpTail, genericList **newStruct, int pos);

// Aloca espaço para uma nó da lista generica
genericList *allocGenericList();

// Retorna o ponteiro para data
void *getData(genericList *tmpStruct);

// Retorna o ponteiro para next
void *getNext(genericList *tmpStruct);

// Retorna type
int getType(genericList *tmpStruct);

#endif //GENERICLIST_H
