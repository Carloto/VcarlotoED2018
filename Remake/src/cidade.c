// Include
#include "cidade.h"

struct tmpCidade { // Estruturas da cidade
    FILE *quadras; // Arquivo binario de quadras
    bTree quadraTree; // Arvore contendo os enderecos do arquivo binario
    FILE *hidrantes; // Arquivo binario de hidrantes
    bTree hidrTree; // Arvore contendo os enderecos do arquivo binario
    FILE *semaforos; // Arquivo binario de semaforos
    bTree semafTree; // Arvore contendo os enderecos do arquivo binario
    FILE *torres; // Arquivo binario de torres
    bTree torreTree; // Arvore contendo os enderecos do arquivo binario
};

// Aloca e inicializa uma struct Cidade
Cidade *allocCidade(fileArguments *source) {
    Cidade *tmpStruct = (Cidade *) calloc(1, sizeof(Cidade));
    char *openName = NULL; // Nome de abertura do arquivo
    char *name = (char *) calloc(50, sizeof(char)); // Nome da estrutura

    sprintf(name, "%s", "quadra"); // Quadra
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->quadras = openFile(openName, "wb+");
    tmpStruct->quadraTree = btCreate();

    sprintf(name, "%s", "hidrante"); // Hidrante
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->hidrantes = openFile(openName, "wb+");
    tmpStruct->hidrTree = btCreate();

    sprintf(name, "%s", "semaforo"); // Semaforo
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->semaforos = openFile(openName, "wb+");
    tmpStruct->semafTree = btCreate();

    sprintf(name, "%s", "torre"); // Torre
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->torres = openFile(openName, "wb+");
    tmpStruct->torreTree = btCreate();

    freeString(&openName);
    freeString(&name);
    return tmpStruct;
}

// Libera a memoria de toda a Cidade
void killCidade(Cidade **cityIndex) {
    fclose((*cityIndex)->quadras);
    btDestroy((*cityIndex)->quadraTree);
    fclose((*cityIndex)->hidrantes);
    btDestroy((*cityIndex)->hidrTree);
    fclose((*cityIndex)->semaforos);
    btDestroy((*cityIndex)->semafTree);
    fclose((*cityIndex)->torres);
    btDestroy((*cityIndex)->torreTree);
    free(*cityIndex);
}

// Adiciona uma nova estrutura no arquivo binario e na b-tree, a partir do arquivo lido
void newCityShapeFromFile(Cidade *cityIndex, char *inputLine, Color *colorIndex, int typeOfData) {
    Quadra *tmpQuad = NULL;
    Hidrante *tmpHid = NULL;
    Semaforo *tmpSemaf = NULL;
    Torre *tmpTorre = NULL;
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    // Switch typeOfData
    switch (typeOfData) {
        case 1: // Quadra
            tmpQuad = allocQuadra();
            token = strtok(NULL, " "); // Cep
            setQuadraCep(tmpQuad, token);
            btInsert(cityIndex->quadraTree, hash((unsigned char *) token), ftell(cityIndex->quadras));
            setQuadraX(tmpQuad, newAtod(strtok(NULL, " "))); // X
            setQuadraY(tmpQuad, newAtod(strtok(NULL, " "))); // Y
            setQuadraWidth(tmpQuad, newAtod(strtok(NULL, " "))); // Width
            setQuadraHeight(tmpQuad, newAtod(strtok(NULL, " "))); // Height
            setQuadraStrokeColor(tmpQuad, getQuadStrokeColor(colorIndex));
            setQuadraFillColor(tmpQuad, getQuadFillColor(colorIndex));
            printToBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
            killQuadra(tmpQuad);
            break;
        case 2: // Hidrante
            tmpHid = allocHidrante();
            token = strtok(NULL, " "); // Id
            setHidranteId(tmpHid, token);
            btInsert(cityIndex->hidrTree, hash((unsigned char *) token), ftell(cityIndex->hidrantes));
            setHidranteX(tmpHid, newAtod(strtok(NULL, " "))); // X
            setHidranteY(tmpHid, newAtod(strtok(NULL, " "))); // Y
            setHidranteRadius(tmpHid, 8); // Radius
            setHidranteStrokeColor(tmpHid, getHidStrokeColor(colorIndex));
            setHidranteFillColor(tmpHid, getHidFillColor(colorIndex));
            printToBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
            killHidrante(tmpHid);
            break;
        case 3: // Semaforo
            tmpSemaf = allocSemaforo();
            token = strtok(NULL, " "); // Id
            setSemaforoId(tmpSemaf, token);
            btInsert(cityIndex->semafTree, hash((unsigned char *) token), ftell(cityIndex->semaforos));
            setSemaforoX(tmpSemaf, newAtod(strtok(NULL, " "))); // X
            setSemaforoY(tmpSemaf, newAtod(strtok(NULL, " "))); // Y
            setSemaforoWidth(tmpSemaf, 15); // Width
            setSemaforoHeight(tmpSemaf, 35); // Height
            setSemaforoStrokeColor(tmpSemaf, getSemafStrokeColor(colorIndex));
            setSemaforoFillColor(tmpSemaf, getSemafFillColor(colorIndex));
            printToBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
            killSemaforo(tmpSemaf);
            break;
        case 4: // Torre
            tmpTorre = allocTorre();
            token = strtok(NULL, " "); // Id
            setTorreId(tmpTorre, token);
            btInsert(cityIndex->torreTree, hash((unsigned char *) token), ftell(cityIndex->torres));
            setTorreX(tmpTorre, newAtod(strtok(NULL, " "))); // X
            setTorreY(tmpTorre, newAtod(strtok(NULL, " "))); // Y
            setTorreRadius(tmpTorre, 8); // Radius
            setTorreStrokeColor(tmpTorre, getTorStrokeColor(colorIndex));
            setTorreFillColor(tmpTorre, getTorFillColor(colorIndex));
            printToBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
            killTorre(tmpTorre);
            break;
        default:
            break;
    }
}

// Retorna um ponteiro para o arquivo requisitado
FILE **getCityFile(Cidade *cityIndex, int action) {
    switch (action) {
        case 1: // Quadras
            return &(cityIndex->quadras);
        case 2: // Semaforos
            return &(cityIndex->semaforos);
        case 3: // Hidrantes
            return &(cityIndex->hidrantes);
        case 4: // Torres
            return &(cityIndex->torres);
        default:
            break;
    }
    return NULL;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getQuadraAddress(Cidade *cityIndex, unsigned long id, long int *address, Quadra **aux) {
    if (btGetAddress(cityIndex->quadraTree, id, address)) {
        *aux = allocQuadra();
        fseek(cityIndex->quadras, *address, SEEK_SET);
        readFromBin(&(cityIndex->quadras), getQuadraSize(), *aux);
        return 1;
    }
    return 0;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getSemaforoAddress(Cidade *cityIndex, unsigned long id, long int *address, Semaforo **aux) {
    if (btGetAddress(cityIndex->semafTree, id, address)) {
        *aux = allocSemaforo();
        fseek(cityIndex->semaforos, *address, SEEK_SET);
        readFromBin(&(cityIndex->semaforos), getSemaforoSize(), *aux);
        return 1;
    }
    return 0;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getHidranteAddress(Cidade *cityIndex, unsigned long id, long int *address, Hidrante **aux) {
    if (btGetAddress(cityIndex->hidrTree, id, address)) {
        *aux = allocHidrante();
        fseek(cityIndex->hidrantes, *address, SEEK_SET);
        readFromBin(&(cityIndex->hidrantes), getHidranteSize(), *aux);
        return 1;
    }
    return 0;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getTorreAddress(Cidade *cityIndex, unsigned long id, long int *address, Torre **aux) {
    if (btGetAddress(cityIndex->torreTree, id, address)) {
        *aux = allocTorre();
        fseek(cityIndex->torres, *address, SEEK_SET);
        readFromBin(&(cityIndex->torres), getTorreSize(), *aux);
        return 1;
    }
    return 0;
}

// Verifica quais quadras estão dentro de dado retangulo
void quadraInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                           double aHeigth, int action) {
    printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    long int address;
    Quadra *tmpQuad = allocQuadra();
    fseek(cityIndex->quadras, 0, SEEK_SET);
    while (!feof(cityIndex->quadras)) {
        readFromBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
        if (!feof(cityIndex->quadras)) {
            if (rectInsideRect(aX, aY, aWidth, aHeigth, getQuadraX(tmpQuad), getQuadraY(tmpQuad),
                               getQuadraWidth(tmpQuad), getQuadraHeight(tmpQuad)) == 1) {
                if (checkString(getQuadraCep(tmpQuad))) {
                    fprintf(*txtOutput,
                            "Cep = %s  X = %lf  Y = %lf  Width = %lf  Height = %lf  Stroke = %s  Fill = %s\n",
                            getQuadraCep(tmpQuad), getQuadraX(tmpQuad),
                            getQuadraY(tmpQuad), getQuadraWidth(tmpQuad), getQuadraHeight(tmpQuad),
                            getQuadraStrokeColor(tmpQuad), getQuadraFillColor(tmpQuad));

                    switch (action) {
                        case 2: // dq
                            btDeleteInfo(cityIndex->quadraTree, hash((unsigned char *) getQuadraCep(tmpQuad)),
                                         &address);
                            deleteQuadra(tmpQuad);
                            fseek(cityIndex->quadras, address, SEEK_SET);
                            printToBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killQuadra(tmpQuad);
}

// Verifica quais quadras estão dentro de dado circulo
void quadraInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double radius,
                        int action) {
    printDashCircle(svgOutput, aX, aY, radius);
    long int address;
    Quadra *tmpQuad = allocQuadra();
    fseek(cityIndex->quadras, 0, SEEK_SET);
    while (!feof(cityIndex->quadras)) {
        readFromBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
        if (!feof(cityIndex->quadras)) {
            if (pointInsideCircle(getQuadraX(tmpQuad), getQuadraY(tmpQuad), aX, aY, radius) &&
                pointInsideCircle(getQuadraX(tmpQuad) + getQuadraWidth(tmpQuad), getQuadraY(tmpQuad), aX, aY, radius) &&
                pointInsideCircle(getQuadraX(tmpQuad), getQuadraY(tmpQuad) + getQuadraHeight(tmpQuad), aX, aY,
                                  radius) &&
                pointInsideCircle(getQuadraX(tmpQuad) + getQuadraWidth(tmpQuad),
                                  getQuadraY(tmpQuad) + getQuadraHeight(tmpQuad), aX, aY, radius)) {
                if (checkString(getQuadraCep(tmpQuad))) {
                    fprintf(*txtOutput,
                            "Cep = %s  X = %lf  Y = %lf  Width = %lf  Height = %lf  Stroke = %s  Fill = %s\n",
                            getQuadraCep(tmpQuad), getQuadraX(tmpQuad),
                            getQuadraY(tmpQuad), getQuadraWidth(tmpQuad), getQuadraHeight(tmpQuad),
                            getQuadraStrokeColor(tmpQuad), getQuadraFillColor(tmpQuad));

                    switch (action) {
                        case 2: // dq
                            btDeleteInfo(cityIndex->quadraTree, hash((unsigned char *) getQuadraCep(tmpQuad)),
                                         &address);
                            deleteQuadra(tmpQuad);
                            fseek(cityIndex->quadras, address, SEEK_SET);
                            printToBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killQuadra(tmpQuad);
}

// Verifica quais semaforos estão dentro de dado retangulo
void semafInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                          double aHeigth, int action) {
    printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    long int address;
    Semaforo *tmpSemaf = allocSemaforo();
    fseek(cityIndex->semaforos, 0, SEEK_SET);
    while (!feof(cityIndex->semaforos)) {
        readFromBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
        if (!feof(cityIndex->semaforos)) {
            if (pointInsideRectangle(getSemaforoX(tmpSemaf), getSemaforoY(tmpSemaf), aX, aY, aWidth, aHeigth) == 1) {
                if (checkString(getSemaforoId(tmpSemaf))) {

                    fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                            getSemaforoId(tmpSemaf), getSemaforoX(tmpSemaf),
                            getSemaforoY(tmpSemaf),
                            getSemaforoStrokeColor(tmpSemaf), getSemaforoFillColor(tmpSemaf));

                    switch (action) {
                        case 2: // dle
                            btDeleteInfo(cityIndex->semafTree, hash((unsigned char *) getSemaforoId(tmpSemaf)),
                                         &address);
                            deleteSemaforo(tmpSemaf);
                            fseek(cityIndex->semaforos, address, SEEK_SET);
                            printToBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killSemaforo(tmpSemaf);
}

// Verifica quais semaforos estão dentro de dado circulo
void semafInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double radius,
                       int action) {
    printDashCircle(svgOutput, aX, aY, radius);
    long int address;
    Semaforo *tmpSemaf = allocSemaforo();
    fseek(cityIndex->semaforos, 0, SEEK_SET);
    while (!feof(cityIndex->semaforos)) {
        readFromBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
        if (!feof(cityIndex->semaforos)) {
            if (pointInsideCircle(getSemaforoX(tmpSemaf), getSemaforoY(tmpSemaf), aX, aY, radius)) {
                if (checkString(getSemaforoId(tmpSemaf))) {

                    fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                            getSemaforoId(tmpSemaf), getSemaforoX(tmpSemaf),
                            getSemaforoY(tmpSemaf),
                            getSemaforoStrokeColor(tmpSemaf), getSemaforoFillColor(tmpSemaf));

                    switch (action) {
                        case 2: // dle
                            btDeleteInfo(cityIndex->semafTree, hash((unsigned char *) getSemaforoId(tmpSemaf)),
                                         &address);
                            deleteSemaforo(tmpSemaf);
                            fseek(cityIndex->semaforos, address, SEEK_SET);
                            printToBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killSemaforo(tmpSemaf);
}

// Verifica quais hidrantes estão dentro de dado retangulo
void hidInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                        double aHeigth, int action) {
    printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    long int address;
    Hidrante *tmpHid = allocHidrante();
    fseek(cityIndex->hidrantes, 0, SEEK_SET);
    while (!feof(cityIndex->hidrantes)) {
        readFromBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
        if (!feof(cityIndex->hidrantes)) {
            if (pointInsideRectangle(getHidranteX(tmpHid), getHidranteY(tmpHid), aX, aY, aWidth, aHeigth) == 1) {
                if (checkString(getHidranteId(tmpHid))) {

                    fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                            getHidranteId(tmpHid), getHidranteX(tmpHid),
                            getHidranteY(tmpHid),
                            getHidranteStrokeColor(tmpHid), getHidranteFillColor(tmpHid));

                    switch (action) {
                        case 2: // dle
                            btDeleteInfo(cityIndex->hidrTree, hash((unsigned char *) getHidranteId(tmpHid)), &address);
                            deleteHidrante(tmpHid);
                            fseek(cityIndex->hidrantes, address, SEEK_SET);
                            printToBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killHidrante(tmpHid);
}

// Verifica quais hidrantes estão dentro de dado circulo
void hidInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double radius,
                     int action) {
    printDashCircle(svgOutput, aX, aY, radius);
    long int address;
    Hidrante *tmpHid = allocHidrante();
    fseek(cityIndex->hidrantes, 0, SEEK_SET);
    while (!feof(cityIndex->hidrantes)) {
        readFromBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
        if (!feof(cityIndex->hidrantes)) {
            if (pointInsideCircle(getHidranteX(tmpHid), getHidranteY(tmpHid), aX, aY, radius)) {
                if (checkString(getHidranteId(tmpHid))) {

                    fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                            getHidranteId(tmpHid), getHidranteX(tmpHid),
                            getHidranteY(tmpHid),
                            getHidranteStrokeColor(tmpHid), getHidranteFillColor(tmpHid));

                    switch (action) {
                        case 2: // dle
                            btDeleteInfo(cityIndex->hidrTree, hash((unsigned char *) getHidranteId(tmpHid)), &address);
                            deleteHidrante(tmpHid);
                            fseek(cityIndex->hidrantes, address, SEEK_SET);
                            printToBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killHidrante(tmpHid);
}

// Verifica quais torres estão dentro de dado retangulo
void torreInsideRectangle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double aWidth,
                          double aHeigth, int action) {
    printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    long int address;
    Torre *tmpTorre = allocTorre();
    fseek(cityIndex->torres, 0, SEEK_SET);
    while (!feof(cityIndex->torres)) {
        readFromBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
        if (!feof(cityIndex->torres)) {
            if (pointInsideRectangle(getTorreX(tmpTorre), getTorreY(tmpTorre), aX, aY, aWidth, aHeigth) == 1) {
                if (checkString(getTorreId(tmpTorre))) {

                    fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                            getTorreId(tmpTorre), getTorreX(tmpTorre),
                            getTorreY(tmpTorre),
                            getTorreStrokeColor(tmpTorre), getTorreFillColor(tmpTorre));

                    switch (action) {
                        case 2: // dle
                            btDeleteInfo(cityIndex->torreTree, hash((unsigned char *) getTorreId(tmpTorre)), &address);
                            deleteTorre(tmpTorre);
                            fseek(cityIndex->torres, address, SEEK_SET);
                            printToBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killTorre(tmpTorre);
}

// Verifica quais torres estão dentro de dado circulo
void torreInsideCircle(Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput, double aX, double aY, double radius,
                       int action) {
    printDashCircle(svgOutput, aX, aY, radius);
    long int address;
    Torre *tmpTorre = allocTorre();
    fseek(cityIndex->torres, 0, SEEK_SET);
    while (!feof(cityIndex->torres)) {
        readFromBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
        if (!feof(cityIndex->torres)) {
            if (pointInsideCircle(getTorreX(tmpTorre), getTorreY(tmpTorre), aX, aY, radius)) {
                if (checkString(getTorreId(tmpTorre))) {

                    fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                            getTorreId(tmpTorre), getTorreX(tmpTorre),
                            getTorreY(tmpTorre),
                            getTorreStrokeColor(tmpTorre), getTorreFillColor(tmpTorre));

                    switch (action) {
                        case 2: // dle
                            btDeleteInfo(cityIndex->torreTree, hash((unsigned char *) getTorreId(tmpTorre)), &address);
                            deleteTorre(tmpTorre);
                            fseek(cityIndex->torres, address, SEEK_SET);
                            printToBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
    killTorre(tmpTorre);
}

// Imprime as estruturas da cidade
void printCityShapes(Cidade *cityIndex) {
    // Quadra
    Quadra *tmpQuad = allocQuadra();
    fseek(cityIndex->quadras, 0, SEEK_SET);
    printf("\n\n Quadras \n");
    while (!feof(cityIndex->quadras)) {
        readFromBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
        if (!feof(cityIndex->quadras)) {
            if (checkString(getQuadraCep(tmpQuad))) {
                printQuadra(tmpQuad);
            }
        }
    }
    killQuadra(tmpQuad);

    // Hidrante
    Hidrante *tmpHid = allocHidrante();
    fseek(cityIndex->hidrantes, 0, SEEK_SET);
    printf("\n\n Hidrantes \n");
    while (!feof(cityIndex->hidrantes)) {
        readFromBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
        if (!feof(cityIndex->hidrantes)) {
            if (checkString(getHidranteId(tmpHid))) {
                printHidrante(tmpHid);
            }
        }
    }
    killHidrante(tmpHid);

    // Semaforo
    Semaforo *tmpSemaf = allocSemaforo();
    fseek(cityIndex->semaforos, 0, SEEK_SET);
    printf("\n\n Semaforos \n");
    while (!feof(cityIndex->semaforos)) {
        readFromBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
        if (!feof(cityIndex->semaforos)) {
            if (checkString(getSemaforoId(tmpSemaf))) {
                printSemaforo(tmpSemaf);
            }
        }
    }
    killSemaforo(tmpSemaf);

    // Torre
    Torre *tmpTorre = allocTorre();
    fseek(cityIndex->torres, 0, SEEK_SET);
    printf("\n\n Torres \n");
    while (!feof(cityIndex->torres)) {
        readFromBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
        if (!feof(cityIndex->torres)) {
            if (checkString(getTorreId(tmpTorre))) {
                printTorre(tmpTorre);
            }
        }
    }
    killTorre(tmpTorre);
}

// Imprime a lista de estruturas da cidade no arquivo de saida .svg
void printCityShapesToSvg(Cidade *cityIndex, FILE **outputFile) {
    // Imprimir quadras
    Quadra *tmpQuad = allocQuadra();
    fseek(cityIndex->quadras, 0, SEEK_SET);
    while (!feof(cityIndex->quadras)) {
        readFromBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
        if (!feof(cityIndex->quadras)) {
            if (checkString(getQuadraCep(tmpQuad))) {
                fprintf(*outputFile,
                        "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" ",
                        getQuadraX(tmpQuad),
                        getQuadraY(tmpQuad),
                        getQuadraWidth(tmpQuad),
                        getQuadraHeight(tmpQuad));
                fprintf(*outputFile,
                        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" />\n",
                        getQuadraStrokeColor(tmpQuad),
                        getQuadraFillColor(tmpQuad));
                fprintf(*outputFile,
                        "\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5;\" >%s</text>\n",
                        (getQuadraWidth(tmpQuad) / 2) + getQuadraX(tmpQuad),
                        (getQuadraHeight(tmpQuad) / 2) + getQuadraY(tmpQuad),
                        getQuadraCep(tmpQuad));
            }
        }
    }
    killQuadra(tmpQuad);

    // Imprimir hidrantes
    Hidrante *tmpHid = allocHidrante();
    fseek(cityIndex->hidrantes, 0, SEEK_SET);
    while (!feof(cityIndex->hidrantes)) {
        readFromBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
        if (!feof(cityIndex->hidrantes)) {
            if (checkString(getHidranteId(tmpHid))) {
                fprintf(*outputFile,
                        "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" ",
                        getHidranteX(tmpHid),
                        getHidranteY(tmpHid),
                        getHidranteRadius(tmpHid));
                fprintf(*outputFile,
                        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n",
                        getHidranteStrokeColor(tmpHid),
                        getHidranteFillColor(tmpHid));
                fprintf(*outputFile,
                        "\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" >%s</text>\n",
                        getHidranteX(tmpHid),
                        getHidranteY(tmpHid) + getHidranteRadius(tmpHid) / 2,
                        "H");
            }
        }
    }
    killHidrante(tmpHid);

    // Imprimir semaforo
    Semaforo *tmpSemaf = allocSemaforo();
    fseek(cityIndex->semaforos, 0, SEEK_SET);
    while (!feof(cityIndex->semaforos)) {
        readFromBin(&(cityIndex->semaforos), getSemaforoSize(), tmpSemaf);
        if (!feof(cityIndex->semaforos)) {
            if (checkString(getSemaforoId(tmpSemaf))) {
                fprintf(*outputFile,
                        "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" ",
                        getSemaforoX(tmpSemaf),
                        getSemaforoY(tmpSemaf),
                        getSemaforoWidth(tmpSemaf),
                        getSemaforoHeight(tmpSemaf));
                fprintf(*outputFile,
                        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" />\n",
                        getSemaforoStrokeColor(tmpSemaf),
                        getSemaforoFillColor(tmpSemaf));
                fprintf(*outputFile,
                        "\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" >%s</text>\n",
                        (getSemaforoWidth(tmpSemaf) / 2) + getSemaforoX(tmpSemaf),
                        (getSemaforoHeight(tmpSemaf) / 2) + getSemaforoY(tmpSemaf),
                        "S");
            }
        }
    }
    killSemaforo(tmpSemaf);

    // Imprimir torres
    Torre *tmpTorre = allocTorre();
    fseek(cityIndex->torres, 0, SEEK_SET);
    while (!feof(cityIndex->torres)) {
        readFromBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
        if (!feof(cityIndex->torres)) {
            if (checkString(getTorreId(tmpTorre))) {
                fprintf(*outputFile,
                        "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" ",
                        getTorreX(tmpTorre),
                        getTorreY(tmpTorre),
                        getTorreRadius(tmpTorre));
                fprintf(*outputFile,
                        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n",
                        getTorreStrokeColor(tmpTorre),
                        getTorreFillColor(tmpTorre));
                fprintf(*outputFile,
                        "\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" >%s</text>\n",
                        getTorreX(tmpTorre),
                        getTorreY(tmpTorre) + getTorreRadius(tmpTorre) / 2,
                        "T");
            }
        }
    }
    killTorre(tmpTorre);
}
