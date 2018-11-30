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
            setRectangleWidth(tmpRect, newAtod(strtok(NULL, " "))); // Width
            setRectangleHeight(tmpRect, newAtod(strtok(NULL, " "))); // Height
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
void printBasicShapesToSvg(BasicShapes *shapesIndex, FILE **outputFile) {
    genericList *aux = *(shapesIndex->ShapesHead);
    while (aux != NULL) {
        switch (getType(aux)) {
            case 1: // Circulo
                fprintf(*outputFile, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" ",
                        *getCircleX((Circle *) getData(aux)),
                        *getCircleY((Circle *) getData(aux)),
                        *getCircleRadius((Circle *) getData(aux)));
                fprintf(*outputFile, "stroke=\"%s\" fill=\"%s\"/>\n",
                        getCircleStrokeColor((Circle *) getData(aux)),
                        getCircleFillColor((Circle *) getData(aux)));
                break;
            case 2: // Retangulo
                fprintf(*outputFile, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" ",
                        *getRectangleX((Rectangle *) getData(aux)),
                        *getRectangleY((Rectangle *) getData(aux)),
                        *getRectangleWidth((Rectangle *) getData(aux)),
                        *getRectangleHeight((Rectangle *) getData(aux)));
                fprintf(*outputFile, "stroke=\"%s\" fill=\"%s\"/>\n",
                        getRectangleStrokeColor((Rectangle *) getData(aux)),
                        getRectangleFillColor((Rectangle *) getData(aux)));
                break;
            default:
                break;
        }
        aux = getNext(aux);
    }

}

// Encontra uma figura na lista a partir de um id
int searchBasicShapesId(BasicShapes *tmpShapes, genericList **tmpNode, int id) {
    genericList *aux = *(tmpShapes->ShapesHead);
    while (aux != NULL) {
        switch (getType(aux)) {
            case 1: // Circulo
                if (id == *getCircleId((Circle *) getData(aux))) {
                    *tmpNode = aux;
                    return 1;
                }
                break;
            case 2: // Retangulo
                if (id == *getRectangleId((Rectangle *) getData(aux))) {
                    *tmpNode = aux;
                    return 2;
                }
                break;
            default:
                break;
        }
        aux = getNext(aux);
    }
    return 0; // Id não encontrado
}

// Verifica se um ponto é interno a uma figura
void insideBasicShapes(BasicShapes *tmpShapes, char *inputLine, FILE **outputFile) {
    int id;
    double pointX, pointY;
    genericList *aux = NULL;
    fprintf(*outputFile, "%s\n", inputLine);
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    id = newAtoi(strtok(NULL, " ")); // Id
    pointX = newAtod(strtok(NULL, " ")); // Coordenada X
    pointY = newAtod(strtok(NULL, " ")); // Coordenada Y
    switch (searchBasicShapesId(tmpShapes, &aux, id)) {
        case 1: // Circulo
            if (pointInsideCircle(pointX, pointY, *getCircleX((Circle *) getData(aux)),
                                  *getCircleY((Circle *) getData(aux)),
                                  *getCircleRadius((Circle *) getData(aux))) == 1) {
                fprintf(*outputFile, "SIM\n");
            } else {
                fprintf(*outputFile, "NAO\n");
            }
            break;
        case 2: // Retangulo
            if (pointInsideRectangle(pointX, pointY, *getRectangleX((Rectangle *) getData(aux)),
                                     *getRectangleY((Rectangle *) getData(aux)),
                                     *getRectangleWidth((Rectangle *) getData(aux)),
                                     *getRectangleHeight((Rectangle *) getData(aux))) == 1) {
                fprintf(*outputFile, "SIM\n");
            } else {
                fprintf(*outputFile, "NAO\n");
            }
            break;
        default:
            break;
    }

}

// Calcula a distancia entre duas figuras basicas
void distanceBasicShapes(BasicShapes *tmpShapes, char *inputLine, FILE **outputFile) {
    int id1, id2, check, controle;
    double distance = 0;
    genericList *first = NULL;
    genericList *second = NULL;
    fprintf(*outputFile, "%s\n", inputLine);
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    id1 = newAtoi(strtok(NULL, " ")); // Id1
    id2 = newAtoi(strtok(NULL, " ")); // Id2
    controle = searchBasicShapesId(tmpShapes, &second, id1);
    if (controle == 1) { // Circulo
        first = second;
        check = searchBasicShapesId(tmpShapes, &second, id2);
        if (check == 1) { // first == Circle && second == Circle
            distance = findDistance(*getCircleX((Circle *) getData(first)), *getCircleY((Circle *) getData(first)),
                                    *getCircleX((Circle *) getData(second)), *getCircleY((Circle *) getData(second)));
        } else if (check == 2) { // first == Circle && second == Rectangle
            distance = findDistance(*getCircleX((Circle *) getData(first)), *getCircleY((Circle *) getData(first)),
                                    *getRectangleX((Rectangle *) getData(second)) +
                                    (*getRectangleWidth((Rectangle *) getData(second)) / 2),
                                    *getRectangleY((Rectangle *) getData(second)) +
                                    (*getRectangleHeight((Rectangle *) getData(second)) / 2));
        }
    } else if (controle == 2) { // Retangulo
        check = searchBasicShapesId(tmpShapes, &first, id2);
        if (check == 1) { // first == Circle && second == Rectangle
            distance = findDistance(*getCircleX((Circle *) getData(first)), *getCircleY((Circle *) getData(first)),
                                    *getRectangleX((Rectangle *) getData(second)) +
                                    (*getRectangleWidth((Rectangle *) getData(second)) / 2),
                                    *getRectangleY((Rectangle *) getData(second)) +
                                    (*getRectangleHeight((Rectangle *) getData(second)) / 2));
        } else if (check == 2) { // first == Rectangle && second == Rectangle
            distance = findDistance(*getRectangleX((Rectangle *) getData(first)) +
                                    (*getRectangleWidth((Rectangle *) getData(first)) / 2),
                                    *getRectangleY((Rectangle *) getData(first)) +
                                    (*getRectangleHeight((Rectangle *) getData(first)) / 2),
                                    *getRectangleX((Rectangle *) getData(second)) +
                                    (*getRectangleWidth((Rectangle *) getData(second)) / 2),
                                    *getRectangleY((Rectangle *) getData(second)) +
                                    (*getRectangleHeight((Rectangle *) getData(second)) / 2));
        }
    }
    fprintf(*outputFile, "%lf\n", distance);
}

// Verifica a sobreposicao fe  duas figuras basicas
void overlapBasicShapes(BasicShapes *tmpShapes, char *inputLine, FILE **outputTxt, FILE **outputSvg) {
    int id1, id2, check, controle, result = 0;
    genericList *first = NULL;
    genericList *second = NULL;
    fprintf(*outputTxt, "%s\n", inputLine);
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    id1 = newAtoi(strtok(NULL, " ")); // Id1
    id2 = newAtoi(strtok(NULL, " ")); // Id2
    controle = searchBasicShapesId(tmpShapes, &second, id1);
    if (controle == 1) { // Circulo
        first = second;
        check = searchBasicShapesId(tmpShapes, &second, id2);
        if (check == 1) { // first == Circle && second == Circle
            result = overlapCircleCircle(*getCircleX((Circle *) getData(first)),
                                         *getCircleY((Circle *) getData(first)),
                                         *getCircleRadius((Circle *) getData(first)),
                                         *getCircleX((Circle *) getData(second)),
                                         *getCircleY((Circle *) getData(second)),
                                         *getCircleRadius((Circle *) getData(second)), 1, outputSvg);
        } else if (check == 2) { // first == Circle && second == Rectangle
            result = overlapCircleRectangle(*getCircleX((Circle *) getData(first)),
                                            *getCircleY((Circle *) getData(first)),
                                            *getCircleRadius((Circle *) getData(first)),
                                            *getRectangleX((Rectangle *) getData(second)),
                                            *getRectangleY((Rectangle *) getData(second)),
                                            *getRectangleWidth((Rectangle *) getData(second)),
                                            *getRectangleHeight((Rectangle *) getData(second)), 1, outputSvg);
        }
    } else if (controle == 2) { // Retangulo
        check = searchBasicShapesId(tmpShapes, &first, id2);
        if (check == 1) { // first == Circle && second == Rectangle
            result = overlapCircleRectangle(*getCircleX((Circle *) getData(first)),
                                            *getCircleY((Circle *) getData(first)),
                                            *getCircleRadius((Circle *) getData(first)),
                                            *getRectangleX((Rectangle *) getData(second)),
                                            *getRectangleY((Rectangle *) getData(second)),
                                            *getRectangleWidth((Rectangle *) getData(second)),
                                            *getRectangleHeight((Rectangle *) getData(second)), 1, outputSvg);
        } else if (check == 2) { // first == Rectangle && second == Rectangle
            result = overlapRectangleRectangle(*getRectangleX((Rectangle *) getData(first)),
                                               *getRectangleY((Rectangle *) getData(first)),
                                               *getRectangleWidth((Rectangle *) getData(first)),
                                               *getRectangleHeight((Rectangle *) getData(first)),
                                               *getRectangleX((Rectangle *) getData(second)),
                                               *getRectangleY((Rectangle *) getData(second)),
                                               *getRectangleWidth((Rectangle *) getData(second)),
                                               *getRectangleHeight((Rectangle *) getData(second)), 1, outputSvg);
        }
    }
    if (result == 1) {
        fprintf(*outputTxt, "SIM\n");
    } else {
        fprintf(*outputTxt, "NAO\n");
    }
}

// Traça linhas a partir do id
void linesFromId(BasicShapes *tmpShapes, char *inputLine, fileArguments *tmpFileNames) {
    char *token = strtok(inputLine, " ");// Comando
    char *sufixo = NULL, *fileName = NULL, *newBaseName = NULL;
    if (token == NULL) {
        return;
    }
    int id = newAtoi(strtok(NULL, " ")); // Id
    token = strtok(NULL, " "); // Sufixo
    copyString(&sufixo, token);
    strcatName(&newBaseName, getBaseName(tmpFileNames), &sufixo, "-");
    strcatFileName(&fileName, getOutputPath(tmpFileNames), &newBaseName, ".svg");
    FILE *outputFile = fopen(fileName, "w");
    printTagSvg(&outputFile, 0);
    genericList *aux = *(tmpShapes->ShapesHead);
    genericList *tmpNode = NULL;
    double pointX = 0, pointY = 0, distance = 0, tx = 0, ty = 0;
    int check = searchBasicShapesId(tmpShapes, &tmpNode, id);
    if (check == 1) { // Circulo
        pointX = *getCircleX((Circle *) getData(tmpNode));
        pointY = *getCircleY((Circle *) getData(tmpNode));
    } else if (check == 2) {
        pointX =
                *getRectangleX((Rectangle *) getData(tmpNode)) + *getRectangleWidth((Rectangle *) getData(tmpNode)) / 2;
        pointY = *getRectangleY((Rectangle *) getData(tmpNode)) +
                 *getRectangleHeight((Rectangle *) getData(tmpNode)) / 2;
    }
    printBasicShapesToSvg(tmpShapes, &outputFile);
    while (aux != NULL) {
        switch (getType(aux)) {
            case 1: // Circulo
                distance = findDistance(pointX, pointY,
                                        *getCircleX((Circle *) getData(aux)), *getCircleY((Circle *) getData(aux)));
                fprintf(outputFile, "\t<line x1=\"%f\" y1=\"%f\" ", pointX, pointY);
                fprintf(outputFile, "x2=\"%f\" y2=\"%f\" ", *getCircleX((Circle *) getData(aux)),
                        *getCircleY((Circle *) getData(aux)));
                fprintf(outputFile, "style=\"stroke:%s\" />", getCircleStrokeColor((Circle *) getData(tmpNode)));
                tx = (pointX + *getCircleX((Circle *) getData(aux))) / 2;
                ty = (pointY + *getCircleY((Circle *) getData(aux))) / 2;
                fprintf(outputFile, "\t<text x=\"%f\" y=\"%f\" fill=\"%s\">%f</text>\n", tx, ty,
                        getCircleStrokeColor((Circle *) getData(tmpNode)), distance);
                break;
            case 2: // Retangulo
                distance = findDistance(pointX, pointY,
                                        *getRectangleX((Rectangle *) getData(aux)) +
                                        (*getRectangleWidth((Rectangle *) getData(aux)) / 2),
                                        *getRectangleY((Rectangle *) getData(aux)) +
                                        (*getRectangleHeight((Rectangle *) getData(aux)) / 2));
                fprintf(outputFile, "\t<line x1=\"%f\" y1=\"%f\" ", pointX, pointY);
                fprintf(outputFile, "x2=\"%f\" y2=\"%f\" ",
                        *getRectangleX((Rectangle *) getData(aux)) + *getRectangleWidth((Rectangle *) getData(aux)) / 2,
                        *getRectangleY((Rectangle *) getData(aux)) +
                        *getRectangleHeight((Rectangle *) getData(aux)) / 2);
                fprintf(outputFile, "style=\"stroke:%s\" />", getCircleStrokeColor((Circle *) getData(tmpNode)));
                tx = (pointX + *getRectangleX((Rectangle *) getData(aux)) +
                          *getRectangleWidth((Rectangle *) getData(aux)) / 2) / 2;
                ty = (pointY + *getRectangleY((Rectangle *) getData(aux)) +
                          *getRectangleHeight((Rectangle *) getData(aux)) / 2) / 2;
                fprintf(outputFile, "\t<text x=\"%f\" y=\"%f\" fill=\"%s\">%f</text>\n", tx, ty,
                        getCircleStrokeColor((Circle *) getData(tmpNode)), distance);
                break;
            default:
                break;
        }
        aux = getNext(aux);
    }
    printTagSvg(&outputFile, 1);
    freeString(&newBaseName);
    freeString(&fileName);
    freeString(&sufixo);
    fclose(outputFile);
}
