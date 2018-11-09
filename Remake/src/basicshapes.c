// Include
#include "basicshapes.h"

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
            case 2:
                killRectangle((Rectangle *) getData(auxList));
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

// Imprime a lista
void printBasicShapes(BasicShapes *tmpShapes) {
    genericList *aux = *(tmpShapes->ShapesHead);
    while (aux != NULL) {
        switch (getType(aux)) {
            case 1:
                printCircle((Circle *) getData(aux));
                break;
            case 2:
                printRectangle((Rectangle *) getData(aux));
                break;
            default:
                break;
        }
        aux = getNext(aux);
    }
}

// Adiciona uma nova figura ao final da lista, a partir do arquivo lido
void newShapeFromFile(BasicShapes *shapesIndex, char *inputLine, int typeOfData) {
    // Novo nó
    genericList *tmpNode = allocGenericList();
    Circle *tmpCircle = NULL;
    Rectangle *tmpRect = NULL;
    // Obter os valores de input
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    // Switch typeOfData
    switch (typeOfData) {
        case 1: // Circulo
            tmpCircle = allocCircle();
            setCircleId(tmpCircle, newAtoi(strtok(NULL, " "))); // Id
            setCircleStrokeColor(tmpCircle, strtok(NULL, " ")); // Stroke color
            setCircleFillColor(tmpCircle, strtok(NULL, " ")); // Fill color
            setCircleRadius(tmpCircle, newAtod(strtok(NULL, " "))); // Raio
            setCircleX(tmpCircle, newAtod(strtok(NULL, " "))); // Coordenada X
            setCircleY(tmpCircle, newAtod(strtok(NULL, " "))); // Coordenada Y
            setNewData(tmpNode, (void *) tmpCircle, typeOfData); // Atribuir ao novo nó
            break;
        case 2: // Retangulo
            tmpRect = allocRectangle();
            setRectangleId(tmpRect, newAtoi(strtok(NULL, " "))); // Id
            setRectangleStrokeColor(tmpRect, strtok(NULL, " ")); // Stroke color
            setRectangleFillColor(tmpRect, strtok(NULL, " ")); // Fill color
            setRectangleWidth(tmpRect, newAtod(strtok(NULL, " "))); // Raio
            setRectangleHeight(tmpRect, newAtod(strtok(NULL, " "))); // Raio
            setRectangleX(tmpRect, newAtod(strtok(NULL, " "))); // Coordenada X
            setRectangleY(tmpRect, newAtod(strtok(NULL, " "))); // Coordenada Y
            setNewData(tmpNode, (void *) tmpRect, typeOfData); // Atribuir ao novo nó
            break;
        default:
            break;
    }

    // Verificar se a lista foi inicializada
    if (*(shapesIndex->ShapesHead) == NULL) { // Inicializar a cabeça
        addNewNode(shapesIndex->ShapesHead, shapesIndex->ShapesTail, &tmpNode, 0);
    } else { // Cabeça já inicializada
        addNewNode(shapesIndex->ShapesHead, shapesIndex->ShapesTail, &tmpNode, 1);
    }
}

// Imprime a lista de figuras no arquivo de saida .svg
