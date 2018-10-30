// Include
#include "basicshapes.h"

struct tmpCircle { // Circulo

    int type; // 0 = figura normal, 1 = pontilhado
    int numberId; // Id da figura
    double radius; // Raio do circulo
    double xCenter; // X do centro
    double yCenter; // Y do centro
    char *fillColor; // Cor interior
    char *strokeColor; // Cor da borda

};

struct tmpRectangle { // Retangulo

    int type; // 0 = figura normal, 1 = pontilhado
    int numberId; // Id da figura
    float xCoord; // X do canto superior esquerdo
    float yCoord; // Y do canto superior esquerdo
    float width; // Largura do ratangulo
    float height; // Altura do retangulo
    char *fillColor; // Cor interior
    char *strokeColor; // Cor da borda

};

struct tmpBasicShapes { // Figuras basicas (circulo e retangulo)

    genericList **ShapesHead; // Cabeça da lista
    genericList **ShapesTail; // Fim da lista

};

// Aloca e inicializa uma struct BasicShapes
BasicShapes *allocBasicShapes() {
    BasicShapes *tmpStruct = (BasicShapes *) calloc(1, sizeof(BasicShapes));
    tmpStruct->ShapesHead = (genericList **) calloc(1, sizeof(genericList *));
    tmpStruct->ShapesTail = (genericList **) calloc(1, sizeof(genericList *));
    return tmpStruct;
}


// Aloca e inicializa uma struct Circle
Circle *allocCircle() {
    Circle *tmpCircle = (Circle *) calloc(1, sizeof(Circle));
    tmpCircle->strokeColor = NULL;
    tmpCircle->fillColor = NULL;
    tmpCircle->type = 0;
    return tmpCircle;
}

// Libera a memoria de toda a lista
void killBasicShapes(BasicShapes *tmpShapes) {
    genericList *auxList;
    genericList **auxHead = tmpShapes->ShapesHead;
    genericList **auxTail = tmpShapes->ShapesTail;
    BasicShapes **auxShapes = &tmpShapes;
    while (*(tmpShapes->ShapesHead) != NULL) {
        auxList = *(tmpShapes->ShapesHead);
        *(tmpShapes->ShapesHead) = (*(tmpShapes->ShapesHead))->next;
        switch (auxList->type) {
            case 1:
                killCircle((Circle **) &(auxList->data));
                break;
            default:
                break;
        }
        free(auxList->data);
        free(auxList);
    }
    free(auxHead);
    free(auxTail);
    free(*auxShapes);
}

// Libera a memoria de um unico circulo
void killCircle(Circle **tmpCircle) {
    if (tmpCircle != NULL) {
        freeString(&(*tmpCircle)->strokeColor);
        freeString(&(*tmpCircle)->fillColor);
    }

}// Libera a memoria de um unico retangulo
void killRectangle(Circle **tmpRectangle) {
    if (tmpRectangle != NULL) {
        freeString(&(*tmpRectangle)->strokeColor);
        freeString(&(*tmpRectangle)->fillColor);
    }
}

// Imprime a lista de circulos
void printBasicShapes(BasicShapes *tmpShapes) {
    genericList *aux = (*tmpShapes->ShapesHead);
    while (aux != NULL) {
        printf("\nid = |%d|", ((Circle *) aux->data)->numberId);
        printf("  raio = |%.3lf|", ((Circle *) aux->data)->radius);
        printf("  x = |%.3lf|", ((Circle *) aux->data)->xCenter);
        printf("  y = |%.3lf|", ((Circle *) aux->data)->yCenter);
        printf("  stroke color = |%s|", ((Circle *) aux->data)->strokeColor);
        printf("  fill color = |%s|\n", ((Circle *) aux->data)->fillColor);
        aux = aux->next;
    }
}

// Adiciona um novo circulo ao final da lista, a partir do arquivo lido
void newCircleFromFile(BasicShapes *shapesIndex, char *inputLine) {
    // Novo nó
    genericList *tmpNode = (genericList *) calloc(1, sizeof(genericList));
    tmpNode->type = 1; // Circulo
    Circle *tmpCircle = allocCircle();

    // Obter os valores de tmpCircle
    printThis(inputLine);
    strtok(inputLine, " ");// Comando
     // Id
    tmpCircle->numberId = newAtoi(strtok(NULL, " ")); // Conversão para inteiro e atribuição
     // Stroke color
    copyString(&(tmpCircle->strokeColor), strtok(NULL, " "));
     // Fill color
    copyString(&(tmpCircle->fillColor), strtok(NULL, " "));
     // Raio
    tmpCircle->radius = newAtod(strtok(NULL, " "));
     // Coordenada X
    tmpCircle->xCenter = newAtod(strtok(NULL, " "));
     // Coordenada Y
    tmpCircle->yCenter = newAtod(strtok(NULL, " "));

    // Atribuir ao novo nó
    tmpNode->data = tmpCircle;

    // Verificar se a lista foi inicializada
    if (*(shapesIndex->ShapesHead) == NULL) { // Inicializar a cabeça
        (*shapesIndex->ShapesHead) = tmpNode;
        (*shapesIndex->ShapesTail) = (*shapesIndex->ShapesHead); // Adicionar ao final
        (*shapesIndex->ShapesTail)->next = NULL;
    } else { // Cabeça já inicializada
        (*shapesIndex->ShapesTail)->next = tmpNode; // Adicionar ao final
        (*shapesIndex->ShapesTail) = (*shapesIndex->ShapesTail)->next;
        (*shapesIndex->ShapesTail)->next = NULL;
    }
}

genericList **returnHead(BasicShapes *AllBasicShapes){
    return AllBasicShapes->ShapesHead;
}

// Imprime a lista de figuras no arquivo de saida .svg