#include "linkedist.h"
#include <stdlib.h>

List *Cria_Lista() {
    List *list;
    list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroyData = NULL;
    return list;
}

void Fecha_Lista(List *list) {
    Free_Lista(list);
    free(list);
}

void Free_Lista(List *list) {
    Node *node, *node0;
    void *data;
    node = list->head;
    while (node != NULL) {
        node0 = node;
        node = node->next;
        data = Quebra_Noz(node0);
        if (list->destroyData) {
            list->destroyData(data);
        }
    }
    list->destroyData = NULL;
    Inicio_Lista(list);
}

void Inicio_Lista(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int Tamanho(List *list) {
    return list->size;
}

int Lista_Vazia(List *list) {
    return list->size == 0;
}

void Deleta_Lista(List *list, FuncDestroyData *destroyData) {
    list->destroyData = destroyData;
}

Node *Inserir(List *list, void *data) {
    Node *node;
    node = Cria_Noz(data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
    (list->size)++;
    return node;
}

Node *Inserir_Primeiro(List *list, void *data) {
    Node *node = Cria_Noz(data);
    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->previous = node;
        node->next = list->head;
        list->head = node;
    }
    (list->size)++;
    return node;
}

Node *Inserir_Segundo(List *list, Node *node, void *data) {
    Node *newNode, *previousNode;
    newNode = NULL;
    if (node != NULL) {
        newNode = Cria_Noz(data);
        previousNode = node->previous;
        if (previousNode == NULL) {
            list->head = newNode;
        } else {
            previousNode->next = newNode;
            newNode->previous = previousNode;
        }
        newNode->next = node;
        node->previous = newNode;
        (list->size)++;
    }
    return newNode;
}

Node *Inserir_Depois(List *list, Node *node, void *data) {
    Node *newNode, *nextNode;
    newNode = NULL;
    if (node != NULL) {
        newNode = Cria_Noz(data);
        nextNode = node->next;
        if (nextNode == NULL) {
            list->tail = newNode;
        } else {
            nextNode->previous = newNode;
            newNode->next = nextNode;
        }
        newNode->previous = node;
        node->next = newNode;
        (list->size)++;
    }
    return newNode;
}

void *Remove_Primeiro(List *list) {
    void *data;
    Node *node;
    data = NULL;
    if (list->head != NULL) {
        node = list->head;
        if (list->head == list->tail) {
            list->head = NULL;
            list->tail = NULL;
        } else {
            list->head = list->head->next;
            list->head->previous = NULL;
        }
        data = Quebra_Noz(node);
        (list->size)--;
    }
    return data;
}

void *Remove_Ultimo(List *list) {
    void *data;
    Node *node;
    data = NULL;
    if (list->tail != NULL) {
        node = list->tail;
        if (list->tail == list->head) {
            list->tail = NULL;
            list->head = NULL;
        } else {
            list->tail = list->tail->previous;
            list->tail->next = NULL;
        }
        data = Quebra_Noz(node);
        (list->size)--;
    }
    return data;
}

void *Remove_Node(List *list, Node *node) {
    void *data = NULL;
    if (node != NULL) {
        if (node->previous == NULL) {
            list->head = node->next;
        } else {
            node->previous->next = node->next;
        }
        if (node->next == NULL) {
            list->tail = node->previous;
        } else {
            node->next->previous = node->previous;
        }
        data = Quebra_Noz(node);
        (list->size)--;
    }
    return data;
}

Node *Volta_Primeiro(List *list) {
    return list->head;
}

Node *Volta_Ultimo(List *list) {
    return list->tail;
}

Node *Cria_Noz(void *data) {
    Node *node;
    node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

void *Quebra_Noz(Node *node) { //deleta o no
    void *data;
    data = get(node);
    free(node);
    return data;
}

Node *Proximo(Node *node) {
    return node->next;
}

Node *Anterior(Node *node) {
    return node->previous;
}

void *get(Node *node) {
    return node->data;
} //ver
