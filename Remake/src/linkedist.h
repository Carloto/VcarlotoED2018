#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (FuncDestroyData)(void *data);

typedef struct _list {
    struct _node *head;
    struct _node *tail;
    int size;
    FuncDestroyData *destroyData;
} List;

typedef struct _node {
    void *data;
    struct _node *next;
    struct _node *previous;
} Node;

// Este modulo lida com listas ligadas

List *Cria_Lista();

void Fecha_Lista(List *list);

void Free_Lista(List *list);

void Inicio_Lista(List *list);

int Tamanho(List *list);

int Lista_Vazia(List *list);

Node *Inserir(List *list, void *data);

Node *Inserir_Primeiro(List *list, void *data);

Node *Inserir_Segundo(List *list, Node *node, void *data);

Node *Inserir_Depois(List *list, Node *node, void *data);

void *Remove_Primeiro(List *list);

void *Remove_Ultimo(List *list);

void *Remove_Node(List *list, Node *node);

Node *Volta_Primeiro(List *list);

Node *Volta_Ultimo(List *list);

Node *Cria_Noz(void *data);

void *Quebra_Noz(Node *node);

void *get(Node *node);

Node *Proximo(Node *node);

Node *Anterior(Node *node);

#endif