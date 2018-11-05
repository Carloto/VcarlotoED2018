// Include
#include "genericlist.h"

struct tmp_genericList { // Lista ligada generica
    void *data;
    int type; // 0 = irrelevante, 1 = circulo, 2 = retangulo
    struct tmp_genericList *next;
};

// Adiciona um tipo de dado ao ponteiro data
void setNewData(genericList *tmpStruct, void *data, int type) {
    (tmpStruct->data) = data; // Atribui novos dados
    tmpStruct->type = type;
    // Atribui um tipo
}

// Adciona um novo nó no inicio ou no final da lista
void addNewNode(genericList **tmpHead, genericList **tmpTail, genericList **newStruct, int pos) {
    // Verificar se a lista foi inicializada
    switch (pos) {
        case 0 : // Adicionar no inicio
            (*tmpHead) = (*newStruct);
            (*tmpTail) = (*tmpHead);
            (*tmpTail)->next = NULL;
            break;

        case 1 : // Adicionar no final
            (*tmpTail)->next = *newStruct;
            (*tmpTail) = (*tmpTail)->next;
            (*tmpTail)->next = NULL;
            break;

        default:
            break;
    }
}

// Aloca espaço para uma nó da lista generica
genericList *allocGenericList() {
    genericList *tmpStruct = (genericList *) calloc(1, sizeof(genericList));
    return tmpStruct;
}

// Retorna o ponteiro para data
void *getData(genericList *tmpStruct) {
    return (tmpStruct->data);
}

// Retorna o ponteiro para next
void *getNext(genericList *tmpStruct) {
    return tmpStruct->next;
}

// Retorna type
int getType(genericList *tmpStruct) {
    return tmpStruct->type;
}
