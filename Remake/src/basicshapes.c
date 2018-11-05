// Include
#include "basicshapes.h"
#include "genericlist.h"

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
    *(tmpStruct->ShapesHead) = NULL;
    tmpStruct->ShapesTail = (genericList **) calloc(1, sizeof(genericList *));
    *(tmpStruct->ShapesTail) = NULL;
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
void killBasicShapes(BasicShapes **tmpShapes) {
    // Referencias dos ponteiros
    genericList *auxList = NULL;
    genericList *auxHead = *((*tmpShapes)->ShapesHead);
    BasicShapes **auxShapes = tmpShapes;

    // Looping de free
    while (auxHead != NULL) {
        auxList = auxHead;
        auxHead = (getNext(auxHead));
        switch (getType(auxList)) {
            case 1:
                killCircle((Circle *) getData(auxList));
                break;

            default:
                break;
        }
        free(getData(auxList));
        free(auxList);
    }

    // Free nos ponteiros duplos
    free((*tmpShapes)->ShapesHead);
    free((*tmpShapes)->ShapesTail);
    free(*auxShapes);
}

// Libera a memoria de um unico circulo
void killCircle(Circle *tmpCircle) {
    if (tmpCircle != NULL) {
        freeString(&(tmpCircle->strokeColor));
        freeString(&(tmpCircle->fillColor));
    }
}

void printBasicShapes(BasicShapes *tmpShapes) {
    genericList *aux = *(tmpShapes->ShapesHead);
    while (aux != NULL) {
        printf("\nid = |%d|", ((Circle *) getData(aux))->numberId);
        printf("  raio = |%.3lf|", ((Circle *) getData(aux))->radius);
        printf("  x = |%.3lf|", ((Circle *) getData(aux))->xCenter);
        printf("  y = |%.3lf|", ((Circle *) getData(aux))->yCenter);
        printf("  stroke color = |%s|", ((Circle *) getData(aux))->strokeColor);
        printf("  fill color = |%s|\n", ((Circle *) getData(aux))->fillColor);
        aux = getNext(aux);
    }
}

// Imprime a lista de circulos
void printOneShapes(Circle *tmpShapes) {
    Circle *aux = tmpShapes;
    printf("\nid = |%d|", aux->numberId);
    printf("  raio = |%.3lf|", aux->radius);
    printf("  x = |%.3lf|", aux->xCenter);
    printf("  y = |%.3lf|", aux->yCenter);
    printf("  stroke color = |%s|", aux->strokeColor);
    printf("  fill color = |%s|\n", aux->fillColor);
}

// Adiciona um novo circulo ao final da lista, a partir do arquivo lido
void newCircleFromFile(BasicShapes *shapesIndex, char *inputLine) {
    // Novo nó
    genericList *tmpNode = allocGenericList();
    Circle *tmpCircle = allocCircle();

    // Obter os valores de tmpCircle
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
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
    setNewData(tmpNode, (void *) tmpCircle, 1);

    // Verificar se a lista foi inicializada
    if (*(shapesIndex->ShapesHead) == NULL) { // Inicializar a cabeça
        addNewNode(shapesIndex->ShapesHead, shapesIndex->ShapesTail, &tmpNode, 0);
    } else { // Cabeça já inicializada
        addNewNode(shapesIndex->ShapesHead, shapesIndex->ShapesTail, &tmpNode, 1);
    }
}

// Imprime a lista de figuras no arquivo de saida .svg
