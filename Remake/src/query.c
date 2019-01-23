// Include
#include "query.h"

// Verifica quais estruturas se encontram totalmente dentro da area requisitada
void strucutreInsideRectangle(Cidade *cityIndex, char *linha, FILE **txtOutput, FILE **svgOutput, int action) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    double x;
    double y;
    double width;
    double height;
    int i = 0;
    switch (action) {
        case 1: // q?
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            width = newAtod(strtok(NULL, " "));
            height = newAtod(strtok(NULL, " "));
            quadraInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            semafInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            hidInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            torreInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            break;
        case 2: // dq
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            width = newAtod(strtok(NULL, " "));
            height = newAtod(strtok(NULL, " "));
            quadraInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
            break;
        case 3: // dle
            token = strtok(NULL, " ");
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            width = newAtod(strtok(NULL, " "));
            height = newAtod(strtok(NULL, " "));
            while (token[i] != '\0') {
                switch (token[i]) {
                    case 's':
                        semafInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
                        break;
                    case 'h':
                        hidInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
                        break;
                    case 'r':
                        torreInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
                        break;
                    default:
                        break;
                }
                i++;
            }
            break;
        default:
            break;
    }
}

// Verifica quais estruturas se encontram totalmente dentro da area requisitada
void structureInsideCircle(Cidade *cityIndex, char *linha, FILE **txtOutput, FILE **svgOutput, int action) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    double x;
    double y;
    double radius;
    int i = 0;
    switch (action) {
        case 1: // Q?
            radius = newAtod(strtok(NULL, " "));
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            quadraInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 1);
            semafInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 1);
            hidInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 1);
            torreInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 1);
            break;
        case 2: // Dq
            radius = newAtod(strtok(NULL, " "));
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            quadraInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 2);
            break;
        case 3: // Dle
            token = strtok(NULL, " ");
            radius = newAtod(strtok(NULL, " "));
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            while (token[i] != '\0') {
                switch (token[i]) {
                    case 's':
                        semafInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 2);
                        break;
                    case 'h':
                        hidInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 2);
                        break;
                    case 'r':
                        torreInsideCircle(cityIndex, txtOutput, svgOutput, x, y, radius, 2);
                        break;
                    default:
                        break;
                }
                i++;
            }
            break;
        default:
            break;
    }
}

// Modifica a cor de dada estrutura
void changeColor(Cidade *cityIndex, char *linha) {
    char *token = strtok(linha, " "); // Comando
    token = strtok(NULL, " "); // Id
    long int address;

    // Quadra
    Quadra *tmpQuad = NULL;
    if (getQuadraAddress(cityIndex, hash((unsigned char *) token), &address, &tmpQuad)) {
        setQuadraStrokeColor(tmpQuad, strtok(NULL, " "));
        setQuadraFillColor(tmpQuad, strtok(NULL, " "));
        fseek(*getCityFile(cityIndex, 1), address, SEEK_SET);
        printToBin(getCityFile(cityIndex, 1), getQuadraSize(), tmpQuad);
        killQuadra(tmpQuad);
        return;
    }

    // Semaforo
    Semaforo *tmpSemaf = NULL;
    if (getSemaforoAddress(cityIndex, hash((unsigned char *) token), &address, &tmpSemaf)) {
        setSemaforoStrokeColor(tmpSemaf, strtok(NULL, " "));
        setSemaforoFillColor(tmpSemaf, strtok(NULL, " "));
        fseek(*getCityFile(cityIndex, 2), address, SEEK_SET);
        printToBin(getCityFile(cityIndex, 2), getSemaforoSize(), tmpSemaf);
        killSemaforo(tmpSemaf);
        return;
    }

    // Hidrante
    Hidrante *tmpHid = NULL;
    if (getHidranteAddress(cityIndex, hash((unsigned char *) token), &address, &tmpHid)) {
        setHidranteStrokeColor(tmpHid, strtok(NULL, " "));
        setHidranteFillColor(tmpHid, strtok(NULL, " "));
        fseek(*getCityFile(cityIndex, 3), address, SEEK_SET);
        printToBin(getCityFile(cityIndex, 3), getHidranteSize(), tmpHid);
        killHidrante(tmpHid);
        return;
    }

    // Torre
    Torre *tmpTorre = NULL;
    if (getTorreAddress(cityIndex, hash((unsigned char *) token), &address, &tmpTorre)) {
        setTorreStrokeColor(tmpTorre, strtok(NULL, " "));
        setTorreFillColor(tmpTorre, strtok(NULL, " "));
        fseek(*getCityFile(cityIndex, 4), address, SEEK_SET);
        printToBin(getCityFile(cityIndex, 4), getTorreSize(), tmpTorre);
        killTorre(tmpTorre);
        return;
    }
}

// Imprime os dados da estrutura requisitada
void reportStructure(Cidade *cityIndex, char *linha, FILE **txtOutput) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    token = strtok(NULL, " "); // Id
    long int address;

    // Quadra
    Quadra *tmpQuad = NULL;
    if (getQuadraAddress(cityIndex, hash((unsigned char *) token), &address, &tmpQuad)) {
        fprintf(*txtOutput,
                "Cep = %s  X = %lf  Y = %lf  Width = %lf  Height = %lf  Stroke = %s  Fill = %s\n",
                getQuadraCep(tmpQuad), getQuadraX(tmpQuad),
                getQuadraY(tmpQuad), getQuadraWidth(tmpQuad), getQuadraHeight(tmpQuad),
                getQuadraStrokeColor(tmpQuad), getQuadraFillColor(tmpQuad));
        killQuadra(tmpQuad);
        return;
    }

    // Semaforo
    Semaforo *tmpSemaf = NULL;
    if (getSemaforoAddress(cityIndex, hash((unsigned char *) token), &address, &tmpSemaf)) {
        fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                getSemaforoId(tmpSemaf), getSemaforoX(tmpSemaf),
                getSemaforoY(tmpSemaf),
                getSemaforoStrokeColor(tmpSemaf), getSemaforoFillColor(tmpSemaf));
        killSemaforo(tmpSemaf);
        return;
    }

    // Hidrante
    Hidrante *tmpHid = NULL;
    if (getHidranteAddress(cityIndex, hash((unsigned char *) token), &address, &tmpHid)) {
        fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                getHidranteId(tmpHid), getHidranteX(tmpHid),
                getHidranteY(tmpHid),
                getHidranteStrokeColor(tmpHid), getHidranteFillColor(tmpHid));
        killHidrante(tmpHid);
        return;
    }

    // Torre
    Torre *tmpTorre = NULL;
    if (getTorreAddress(cityIndex, hash((unsigned char *) token), &address, &tmpTorre)) {
        fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                getTorreId(tmpTorre), getTorreX(tmpTorre),
                getTorreY(tmpTorre),
                getTorreStrokeColor(tmpTorre), getTorreFillColor(tmpTorre));
        killTorre(tmpTorre);
        return;
    }
}
