//
// Created by vcarloto on 25/01/19.
//

#include "grafo.h"

#define INT_MAX 65535

Grafo *Novo_Grafo() {
    Grafo *grafo = (Grafo *) malloc(sizeof(Grafo));
    grafo->verts = Cria_Lista();
    grafo->arestas = Cria_Lista();
    return grafo;
}

float **Inicializa_Mat(float **matriz, int size) {
    matriz = (float **) malloc(sizeof(float *) * size);
    for (int i = 0; i < size; i++) {
        matriz[i] = (float *) malloc(sizeof(float) * size);
    }
    for (int i = 0; i < size; i++) {
        matriz[i] = (float *) malloc(sizeof(float) * size);
        for (int j = 0; j < size; j++) {
            matriz[i][j] = -1;
        }
    }
    return matriz;
}

void Coloca_Aresta(char *src, char *dest, char *ldir, char *lesq, float cmp, float vm, char *nome, Grafo *grafo) {
    Aresta *aresta = (Aresta *) malloc(sizeof(Aresta));
    aresta->src = (char *) malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(aresta->src, src);
    aresta->dest = (char *) malloc(sizeof(char) * (strlen(dest) + 1));
    strcpy(aresta->dest, dest);
    aresta->ldir = (char *) malloc(sizeof(char) * (strlen(ldir) + 1));
    strcpy(aresta->ldir, ldir);
    aresta->lesq = (char *) malloc(sizeof(char) * (strlen(lesq) + 1));
    strcpy(aresta->lesq, lesq);
    aresta->cmp = cmp;
    aresta->vm = vm;
    aresta->nome = (char *) malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(aresta->nome, nome);
    Inserir(grafo->arestas, aresta);

}

void Insere_Variaveis_Vertices(Grafo *grafo) {
    Node *nodeV = grafo->verts->head;
    while (nodeV != NULL) {
        Vertice *vert = (Vertice *) nodeV->data;
        Node *node = grafo->arestas->head;
        while (node != NULL) {
            Aresta *aresta = (Aresta *) node->data;
            if ((strcmp(aresta->src, vert->id) == 0) || (strcmp(aresta->dest, vert->id) == 0)) {
                Inserir(vert->arestas, aresta);
            }
            node = node->next;
        }
        nodeV = nodeV->next;
    }
}

void Print_Matriz(float **matriz, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.1f ", matriz[i][j]);
        }
        printf("\n");
    }
}

void Coloca_Vertices(char *nome, int x, int y, Grafo *grafo, int numericID) {
    Vertice *vert = (Vertice *) malloc(sizeof(Vertice));
    vert->id = (char *) malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(vert->id, nome);
    vert->Ponto.x = x;
    vert->Ponto.y = y;
    vert->numericID = numericID;
    vert->arestas = Cria_Lista();
    Inserir(grafo->verts, vert);
}

float **Insere_Var_Matriz(List *verts, float **matriz) { //tempo decorrente para se chegar de um ponto ao outro
    int size = Tamanho(verts) + 1;
    matriz = Inicializa_Mat(matriz, size);
    Node *node = verts->head;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        List *listSrc = vert->arestas;
        Node *nodeInterno = listSrc->head;
        while (nodeInterno != NULL) {
            Aresta *aresta = (Aresta *) nodeInterno->data;
            Node *checkNode = verts->head;
            while (checkNode != NULL) {
                Vertice *checkVert = (Vertice *) checkNode->data;
                List *checkList = checkVert->arestas;
                Node *finalNode = checkList->head;
                while (finalNode != NULL) {
                    Aresta *arestaEntra = (Aresta *) finalNode->data;
                    if ((strcmp(arestaEntra->src, aresta->src) == 0) &&
                        (strcmp(arestaEntra->dest, aresta->dest) == 0)) {
                        if (strcmp(aresta->src, vert->id) == 0) {
                            if (aresta->vm != 0) {
                                matriz[vert->numericID][checkVert->numericID] = aresta->cmp / aresta->vm;
                            } else {
                                matriz[vert->numericID][checkVert->numericID] = 999999;
                            }
                        } else if (strcmp(aresta->dest, vert->id) == 0) {
                            if (aresta->vm != 0) {
                                matriz[checkVert->numericID][vert->numericID] = aresta->cmp / aresta->vm;
                            } else {
                                matriz[checkVert->numericID][vert->numericID] = 999999;
                            }
                        }
                    }
                    finalNode = finalNode->next;
                }
                checkNode = checkNode->next;
            }
            nodeInterno = nodeInterno->next;
        }
        node = node->next;
    }
    return matriz;
}

Vertice *Vertice_Perto(float x, float y, List *verts) {
    float min = INT_MAX;
    Node *node = verts->head;
    Vertice *vertFinal = NULL;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        float d = sqrt(pow(vert->Ponto.x - x, 2) + pow(vert->Ponto.y - y, 2));
        if (d < min) {
            vertFinal = vert;
            min = d;
        }
        node = node->next;
    }
    return vertFinal;

}

Aresta *Aresta_Entre_Vertices(int indexSrc, int indexDest, List *verts) {
    Vertice *vertSrc = NULL;
    Vertice *vertDest = NULL;
    Node *node = verts->head;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        if (vert->numericID == indexSrc) {
            vertSrc = vert;
        }
        node = node->next;
    }
    node = verts->head;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        if (vert->numericID == indexDest) {
            vertDest = vert;
        }
        node = node->next;
    }
    Aresta *arestaFinal = ArestaFinal(vertDest, vertSrc);
    return arestaFinal;
}

Aresta *ArestaFinal(Vertice *vert1, Vertice *vert2) {
    Aresta *arestaFinal = NULL;
    List *arestasVert1 = vert1->arestas;
    List *arestasVert2 = vert2->arestas;
    Node *node = arestasVert1->head;
    while (node != NULL) {
        Aresta *aresta1 = (Aresta *) node->data;
        Node *node1 = arestasVert2->head;
        while (node1 != NULL) {
            Aresta *aresta2 = (Aresta *) node1->data;
            if (strcmp(aresta1->src, aresta2->src) == 0 && strcmp(aresta1->dest, aresta2->dest) == 0) {
                arestaFinal = aresta1;
            }
            node1 = node1->next;
        }
        node = node->next;
    }
    return arestaFinal;
}

float **Insere_Distancias_Mat(List *verts, float **matriz) { //comprimento das ruas
    int size = Tamanho(verts) + 1;
    matriz = Inicializa_Mat(matriz, size);
    Node *node = verts->head;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        List *listSrc = vert->arestas;
        Node *nodeInterno = listSrc->head;
        while (nodeInterno != NULL) {
            Aresta *aresta = (Aresta *) nodeInterno->data;
            Node *checkNode = verts->head;
            while (checkNode != NULL) {
                Vertice *checkVert = (Vertice *) checkNode->data;
                List *checkList = checkVert->arestas;
                Node *finalNode = checkList->head;
                while (finalNode != NULL) {
                    Aresta *arestaEntra = (Aresta *) finalNode->data;
                    if (strcmp(arestaEntra->dest, aresta->dest) == 0 && strcmp(arestaEntra->src, aresta->src) == 0 &&
                        checkVert->numericID != vert->numericID) {
                        if (strcmp(aresta->src, vert->id) == 0) {
                            matriz[vert->numericID][checkVert->numericID] = aresta->cmp;
                        } else if (strcmp(aresta->dest, vert->id) == 0) {
                            matriz[checkVert->numericID][vert->numericID] = aresta->cmp;
                        }
                    }
                    finalNode = finalNode->next;
                }
                checkNode = checkNode->next;
            }
            nodeInterno = nodeInterno->next;
        }
        node = node->next;
    }
    return matriz;
}

int Indices_Vertices(int index, ponto *vetRegistradores, List *verts) {
    Node *node = verts->head;
    int indexDentro = -1;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        if (vert->Ponto.x == vetRegistradores[index].x && vert->Ponto.y == vetRegistradores[index].y) {
            indexDentro = vert->numericID;
            break;
        }
        node = node->next;
    }
    return indexDentro;
}

int Aresta_Dentro_Vertices(Aresta *aresta, Vertice *vert) {
    List *arestaList = vert->arestas;
    Node *node = arestaList->head;
    while (node != NULL) {
        Aresta *arestaDentro = (Aresta *) node->data;
        if ((strcmp(arestaDentro->src, aresta->src) == 0) && (strcmp(arestaDentro->dest, aresta->dest) == 0)) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}
