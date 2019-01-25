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

// Encontra e reporta as radio-bases mais proximas
void closestTorres(Cidade *cityIndex, char *linha, FILE **txtOutput) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    Point *a = torreToPoint(cityIndex);
    char *aux = (char *) calloc(6, sizeof(char));
    sprintf(aux, "black");
    unsigned long um, dois;
    double distance = closest(a, getNumTorres(cityIndex), &um, &dois);
    fprintf(*txtOutput, "Distancia = %.3lf\n", distance);
//    printClosestPoints(a, getNumTorres(cityIndex));
    long int address;
    // Torre
    Torre *tmpTorre = NULL;
//    for (int i = 0; i < 2; i++) {
    if (getTorreAddress(cityIndex, um, &address, &tmpTorre)) {
        fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                getTorreId(tmpTorre), getTorreX(tmpTorre),
                getTorreY(tmpTorre),
                getTorreStrokeColor(tmpTorre), getTorreFillColor(tmpTorre));
        setTorreStrokeColor(tmpTorre, aux);
        setTorreRadius(tmpTorre, 10);
        fseek(*getCityFile(cityIndex, 4), address, SEEK_SET);
        printToBin(getCityFile(cityIndex, 4), getTorreSize(), tmpTorre);
        killTorre(tmpTorre);
    }
    if (getTorreAddress(cityIndex, dois, &address, &tmpTorre)) {
        fprintf(*txtOutput, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
                getTorreId(tmpTorre), getTorreX(tmpTorre),
                getTorreY(tmpTorre),
                getTorreStrokeColor(tmpTorre), getTorreFillColor(tmpTorre));
        setTorreStrokeColor(tmpTorre, aux);
        setTorreRadius(tmpTorre, 10);
        fseek(*getCityFile(cityIndex, 4), address, SEEK_SET);
        printToBin(getCityFile(cityIndex, 4), getTorreSize(), tmpTorre);
        killTorre(tmpTorre);
    }
//    }
    freeString(&aux);
    free(a);
}

// Imprime os dados do morador requisitado
void reportMorador(Cidade *cityIndex, char *linha, FILE **txtOutput, int action, AuxFigura **tmpAux) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    Pessoa *tmpPessoa = NULL;
    Moradia *tmpMoradia = NULL;
    Quadra *tmpQuad = NULL;
    long int address;
    switch (action) {
        case 1: // Moradia
            token = strtok(NULL, " "); // Cep
            if (getMoradiaAddress(cityIndex, hash((unsigned char *) token), &address, &tmpMoradia,
                                  2)) { // 2 Para busca por cep
                if (getPessoaAddress(cityIndex, hash((unsigned char *) getMoradiaCpf(tmpMoradia)), &address,
                                     &tmpPessoa)) {
                    getQuadraAddress(cityIndex, hash((unsigned char *) getMoradiaCep(tmpMoradia)), &address,
                                     &tmpQuad);
                    pessoaMoradiaTxt(tmpMoradia, tmpPessoa, tmpQuad, txtOutput, 1);
                    killMoradia(tmpMoradia);
                    killPessoa(tmpPessoa);
                } else {
                    fprintf(*txtOutput, "Pessoa não encontrada\n");
                }
                return;
            } else {
                fprintf(*txtOutput, "Casa não encontrada\n");
            }
            break;
        case 2: // Cpf
            token = strtok(NULL, " "); // Cep
            if (getMoradiaAddress(cityIndex, hash((unsigned char *) token), &address, &tmpMoradia,
                                  1)) { // 2 Para busca por cpf
                if (getPessoaAddress(cityIndex, hash((unsigned char *) getMoradiaCpf(tmpMoradia)), &address,
                                     &tmpPessoa)) {
                    getQuadraAddress(cityIndex, hash((unsigned char *) getMoradiaCep(tmpMoradia)), &address,
                                     &tmpQuad);
                    pessoaMoradiaTxt(tmpMoradia, tmpPessoa, tmpQuad, txtOutput, 1);
                    addAuxQuadra(tmpQuad, tmpAux, getMoradiaNum(tmpMoradia), getFaceValue(getMoradiaFace(tmpMoradia)),
                                 1);
                    killMoradia(tmpMoradia);
                    killPessoa(tmpPessoa);
                    killQuadra(tmpQuad);
                } else {
                    fprintf(*txtOutput, "Pessoa não encontrada\n");
                }
                return;
            } else {
                fprintf(*txtOutput, "Casa não encontrada\n");
            }
            break;
        default:
            break;
    }

}

// Imprime os dados do estabelecimento requisitado
void reportEstab(Cidade *cityIndex, char *linha, FILE **txtOutput, int action, AuxFigura **tmpAux) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    Quadra *tmpQuad = NULL;
    Estab *tmpEstab = NULL;
    Tipo *tmpTipo = NULL;
    long int address;
    switch (action) {
        case 1: // Cnpj
            token = strtok(NULL, " "); // Cnpj
            if (getEstabAddress(cityIndex, hash((unsigned char *) token), &address, &tmpEstab)) {
                if (getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(tmpEstab)), &address, &tmpQuad)) {
                    getTipoAddress(cityIndex, hash((unsigned char *) getEstabCodt(tmpEstab)), &address, &tmpTipo);
                    estabQuadraTxt(tmpEstab, tmpTipo, tmpQuad, txtOutput, 1);
                    addAuxQuadra(tmpQuad, tmpAux, getEstabNum(tmpEstab), getFaceValue(getEstabFace(tmpEstab)), 2);
                    killQuadra(tmpQuad);
                    killEstab(tmpEstab);
                    killTipo(tmpTipo);
                } else {
                    fprintf(*txtOutput, "Pessoa não encontrada\n");
                }
                return;
            } else {
                fprintf(*txtOutput, "Casa não encontrada\n");
            }
            break;
        case 2: // Cep (ecq?)
            token = strtok(NULL, " "); // Cep
            if (getQuadraAddress(cityIndex, hash((unsigned char *) token), &address,
                                 &tmpQuad)) {
                reportEstabCep(cityIndex, hash((unsigned char *) getQuadraCep(tmpQuad)), txtOutput,1);
                killQuadra(tmpQuad);
            } else {
                fprintf(*txtOutput, "Cep não encontrada\n");;
            }
            break;
        case 3: // Tipo (ecr?)
            token = strtok(NULL, " "); // Tipo
            if (getTipoAddress(cityIndex, hash((unsigned char *) token), &address,
                               &tmpTipo)) {
                reportEstabCep(cityIndex, hash((unsigned char *) getQuadraCep(tmpQuad)), txtOutput, 1);
                killQuadra(tmpQuad);
            } else {
                fprintf(*txtOutput, "Tipo não encontrada\n");;
            }
            break;
        default:
            break;
    }
}

// Imprime os dados dos moradores dentro da regiao
void reportMoradorRect(Cidade *cityIndex, char *linha, FILE **txtOutput) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    double x = newAtod(strtok(NULL, " ")); // X
    double y = newAtod(strtok(NULL, " ")); // Y
    double width = newAtod(strtok(NULL, " ")); // Width
    double height = newAtod(strtok(NULL, " ")); // Height
    quadraInsideRectangle(cityIndex, txtOutput, NULL, x, y, width, height, 3);
}

// Declara um morador como morto
void ripMorador(Cidade *cityIndex, char *linha, FILE **txtOutput, AuxFigura **tmpAux) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    Pessoa *tmpPessoa = NULL;
    Moradia *tmpMoradia = NULL;
    Quadra *tmpQuad = NULL;
    long int address;
    // Moradia
    token = strtok(NULL, " "); // Cep
    if (getMoradiaAddress(cityIndex, hash((unsigned char *) token), &address, &tmpMoradia,
                          1)) { // 1 Para busca por cpf
        if (getPessoaAddress(cityIndex, hash((unsigned char *) getMoradiaCpf(tmpMoradia)), &address,
                             &tmpPessoa)) {
            getQuadraAddress(cityIndex, hash((unsigned char *) getMoradiaCep(tmpMoradia)), &address,
                             &tmpQuad);
            pessoaMoradiaTxt(tmpMoradia, tmpPessoa, tmpQuad, txtOutput, 4);
            addAuxQuadra(tmpQuad, tmpAux, getMoradiaNum(tmpMoradia), getFaceValue(getMoradiaFace(tmpMoradia)), 3);
            ripPessoa(cityIndex, hash((unsigned char *) getMoradiaCpf(tmpMoradia)));
            killMoradia(tmpMoradia);
            killPessoa(tmpPessoa);
            killQuadra(tmpQuad);
        } else {
            fprintf(*txtOutput, "Pessoa não encontrada\n");
        }
        return;
    } else {
        fprintf(*txtOutput, "Casa não encontrada\n");
    }

}
