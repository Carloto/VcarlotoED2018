// Include
#include "auxfig.h"

struct auxf {               // Codigos de tipo
    double x1;              // 1 para circulo de moradia, 2 para circulo de estab
    double x2;
    double y1;
    double y2;
    int tipo;
    struct auxf *next;
};

// Aloca um no
AuxFigura *allocAux() {
    AuxFigura *tmpaux = (AuxFigura *) calloc(1, sizeof(AuxFigura));
    tmpaux->next = NULL;
    return tmpaux;
}

// Adiciona um no na cabeça
void addAux(AuxFigura **head, double x1, double y1, double x2, double y2, int tipo) {
    AuxFigura *newNode = allocAux();
    newNode->x1 = x1;
    newNode->y1 = y1;
    newNode->x2 = x2;
    newNode->y2 = y2;
    newNode->tipo = tipo;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = (*head);
    (*head) = newNode;
}

// Deleta a arvore
void killAux(AuxFigura **head) {
    AuxFigura *current = *head;
    AuxFigura *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Imprime as figuras auxiliares no svg
void printAuxToSvg(AuxFigura *head, FILE **svgOutput) {
    AuxFigura *tmpAux = head;
    while (tmpAux != NULL) {
        switch (tmpAux->tipo) {
            case 1:
                fprintf(*svgOutput,
                        "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" ",
                        tmpAux->x1,
                        tmpAux->y1);
                fprintf(*svgOutput,
                        "stroke=\"black\" fill=\"lightseagreen\" style=\"stroke-width: 3;\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n");
                break;
            case 2:
                fprintf(*svgOutput,
                        "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" ",
                        tmpAux->x1,
                        tmpAux->y1);
                fprintf(*svgOutput,
                        "stroke=\"black\" fill=\"orangered\" style=\"stroke-width: 3;\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n");
                break;
            default:
                break;
        }
        tmpAux = tmpAux->next;
    }
}
