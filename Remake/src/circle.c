// Include
#include "circle.h"

// Aloca e inicializa uma struct Circle
Circle *allocCircle() {
    Circle *tmpCircle = (Circle *) calloc(1, sizeof(Circle));
    tmpCircle->strokeColor = NULL;
    tmpCircle->fillColor = NULL;
    return tmpCircle;
}

// Libera a memoria da lista ligada de circulos
void killCircle(genericList *tmpCircles) {
    genericList *aux;
    while (tmpCircles != NULL) {
        aux = tmpCircles;
        tmpCircles = tmpCircles->next;
        freeString(&((Circle *) aux->data)->strokeColor);
        freeString(&((Circle *) aux->data)->fillColor);
        free(aux->data);
        free(aux);
    }
}

// Imprime a lista de circulos
void printAllCircles(genericList *tmpCircles) {
    genericList *aux = tmpCircles;
    while (aux != NULL) {
        printf("\nid = |%d|", ((Circle *) aux->data)->numberId);
        printf("  x = |%.2f|", ((Circle *) aux->data)->xCenter);
        printf("  y = |%.2f|", ((Circle *) aux->data)->yCenter);
        printf("  stroke color = |%s|", ((Circle *) aux->data)->strokeColor);
        printf("  fill color = |%s|\n", ((Circle *) aux->data)->fillColor);
        aux = aux->next;
    }
}
