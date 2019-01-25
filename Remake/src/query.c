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
    char *cpf = NULL, *cep = NULL, *compl = NULL, *face = NULL;
    int num;
    Pessoa *tmpPessoa = NULL;
    Moradia *tmpMoradia = NULL;
    Moradia *moradiaAux = NULL;
    Quadra *tmpQuad = NULL;
    Quadra *quadraAux = NULL;
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
                    killQuadra(tmpQuad);
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
        case 3: // Mud
            cpf = strtok(NULL, " "); // Cpf
            cep = strtok(NULL, " "); // Cep
            face = strtok(NULL, " "); // Face
            num = newAtoi(strtok(NULL, " ")); // Num
            compl = strtok(NULL, " "); // Compl
            if (getMoradiaAddress(cityIndex, hash((unsigned char *) cpf), &address, &tmpMoradia,
                                  1)) { // 2 Para busca por cpf
                if (getPessoaAddress(cityIndex, hash((unsigned char *) cpf), &address,
                                     &tmpPessoa)) {
                    getQuadraAddress(cityIndex, hash((unsigned char *) cep), &address,
                                     &tmpQuad);
                    getMoradiaAddress(cityIndex, hash((unsigned char *) getPessoaCpf(tmpPessoa)), &address, &moradiaAux,
                                      1);
                    getQuadraAddress(cityIndex, hash((unsigned char *) getMoradiaCep(moradiaAux)), &address,
                                     &quadraAux);
                    pessoaMoradiaTxt(tmpMoradia, tmpPessoa, quadraAux, txtOutput, 1);
                    addAux(tmpAux, getQuadraX(tmpQuad), getQuadraY(tmpQuad), getQuadraX(quadraAux),
                           getQuadraY(quadraAux), 6);
                    mudaPessoa(cityIndex, cpf, cep, face, compl, num);
                    killMoradia(moradiaAux);
                    killQuadra(quadraAux);
                    getMoradiaAddress(cityIndex, hash((unsigned char *) getPessoaCpf(tmpPessoa)), &address, &moradiaAux,
                                      1);
                    getQuadraAddress(cityIndex, hash((unsigned char *) cep), &address,
                                     &quadraAux);
                    pessoaMoradiaTxt(moradiaAux, tmpPessoa, quadraAux, txtOutput, 1);
                    killMoradia(moradiaAux);
                    killMoradia(tmpMoradia);
                    killPessoa(tmpPessoa);
                    killQuadra(tmpQuad);
                    killQuadra(quadraAux);
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
    char *cnpj = NULL, *cep = NULL, *face = NULL;
    int num;
    Quadra *tmpQuad = NULL, *quadraAux = NULL;
    Estab *tmpEstab = NULL, *estabAux = NULL;
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
                reportEstabCep(cityIndex, hash((unsigned char *) getQuadraCep(tmpQuad)), txtOutput, 1);
                killQuadra(tmpQuad);
            } else {
                fprintf(*txtOutput, "Cep não encontrada\n");;
            }
            break;
        case 3: // Tipo (ecr?)
            token = strtok(NULL, " "); // Tipo
            if (getTipoAddress(cityIndex, hash((unsigned char *) token), &address,
                               &tmpTipo)) {
                token = strtok(NULL, " "); // X (se presente)
                if (token != NULL) {
                    double x = newAtod(token);
                    double y = newAtod(strtok(NULL, " "));
                    double width = newAtod(strtok(NULL, " "));
                    double height = newAtod(strtok(NULL, " "));
                    reportEstabInside(cityIndex, hash((unsigned char *) getTipoCodt(tmpTipo)), txtOutput, 2, x, y,
                                      width, height);
                } else {
                    reportEstabCep(cityIndex, hash((unsigned char *) getTipoCodt(tmpTipo)), txtOutput, 2);
                }
                killTipo(tmpTipo);
            } else {
                fprintf(*txtOutput, "Tipo não encontrada\n");;
            }
            break;
        case 4: // Tipo (tecr?)
            token = strtok(NULL, " "); // Tipo
            double x = newAtod(token); // X
            double y = newAtod(strtok(NULL, " "));// Y
            double width = newAtod(strtok(NULL, " ")); // Width
            double height = newAtod(strtok(NULL, " ")); // Heigth
            reportEstabInside(cityIndex, 0, txtOutput, 5, x, y,
                              width, height);
            break;
        case 5: // fec
            token = strtok(NULL, " "); // Cnpj
            if (getEstabAddress(cityIndex, hash((unsigned char *) token), &address, &tmpEstab)) {
                if (getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(tmpEstab)), &address, &tmpQuad)) {
                    getTipoAddress(cityIndex, hash((unsigned char *) getEstabCodt(tmpEstab)), &address, &tmpTipo);
                    estabQuadraTxt(tmpEstab, tmpTipo, tmpQuad, txtOutput, 1);
                    ripEstab(cityIndex, hash((unsigned char *) getEstabCnpj(tmpEstab)));
                    killQuadra(tmpQuad);
                    killEstab(tmpEstab);
                    killTipo(tmpTipo);
                } else {
                    fprintf(*txtOutput, "Cep não encontrada\n");
                }
                return;
            } else {
                fprintf(*txtOutput, "Cnpj não encontrada\n");
            }
            break;
        case 6: // Mudec
            cnpj = strtok(NULL, " "); // Cnpj
            cep = strtok(NULL, " "); // Cep
            face = strtok(NULL, " "); // Face
            num = newAtoi(strtok(NULL, " ")); // Num
            if (getEstabAddress(cityIndex, hash((unsigned char *) cnpj), &address, &tmpEstab)) {
                if (getQuadraAddress(cityIndex, hash((unsigned char *) cep), &address,
                                     &tmpQuad)) {
                    getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(tmpEstab)), &address,
                                     &quadraAux);
                    getTipoAddress(cityIndex, hash((unsigned char *) getEstabCodt(tmpEstab)), &address, &tmpTipo);
                    estabQuadraTxt(tmpEstab, tmpTipo, quadraAux, txtOutput, 1);
                    addAux(tmpAux, getQuadraX(tmpQuad), getQuadraY(tmpQuad), getQuadraX(quadraAux),
                           getQuadraY(quadraAux), 7);
                    mudaEstab(cityIndex, cnpj, cep, face, num);
                    killEstab(estabAux);
                    killTipo(tmpTipo);
                    killQuadra(quadraAux);
                    getEstabAddress(cityIndex, hash((unsigned char *) cnpj), &address, &estabAux);
                    getTipoAddress(cityIndex, hash((unsigned char *) getEstabCodt(estabAux)), &address, &tmpTipo);
                    getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(estabAux)), &address,
                                     &quadraAux);
                    estabQuadraTxt(estabAux, tmpTipo, quadraAux, txtOutput, 1);
                    killEstab(estabAux);
                    killEstab(tmpEstab);
                    killTipo(tmpTipo);
                    killQuadra(quadraAux);
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

// Reporta o hidrante mais proximo de determinada estrutura
void reportHid(Cidade *cityIndex, char *linha, FILE **txtOutput, int action, AuxFigura **tmpAux) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    Quadra *tmpQuad = NULL;
    Torre *tmpTorre = NULL;
    int face, num;
    long int address;
    switch (action) {
        case 1: // Hidrante mais proximo do endereço (hmpe?)
            token = strtok(NULL, " "); // Cep
            getQuadraAddress(cityIndex, hash((unsigned char *) token), &address, &tmpQuad);
            face = getFaceValue(strtok(NULL, " ")); // Face
            num = newAtoi(strtok(NULL, " ")); // Num
            double x = getQuadraX(tmpQuad); // X
            double y = getQuadraY(tmpQuad);// Y
            double width = getQuadraWidth(tmpQuad); // Width
            double height = getQuadraHeight(tmpQuad); // Heigth
            switch (face) {
                case 1: // Norte
                    x = x + width / 2;
                    break;
                case 2: // Sul
                    x = x + width / 2;
                    y = y + height;
                    break;
                case 3: // Leste
                    y = y + height / 2;
                    break;
                case 4: // Oeste
                    x = x + width;
                    y = y + height / 2;
                default:
                    break;
            }
            closestHidrante(cityIndex, txtOutput, 0, x, y, 1, tmpAux);
            killQuadra(tmpQuad);
            break;
        case 2: // Hidrante mais proximo da torre (hmp?)
            token = strtok(NULL, " "); // Id
            if (getTorreAddress(cityIndex, hash((unsigned char *) token), &address, &tmpTorre)) {
                double x1 = getTorreX(tmpTorre); // X
                double y1 = getTorreY(tmpTorre); // Y
                closestHidrante(cityIndex, txtOutput, hash((unsigned char *) getTorreId(tmpTorre)), x1, y1, 2, tmpAux);
                killTorre(tmpTorre);
            } else {
                fprintf(*txtOutput, "Id não encontrada\n");
            }
            break;
        default:
            break;
    }
}

// Elimina as estruturas dentro da região
void dpr(Cidade *cityIndex, char *linha, FILE **txtOutput, int action, AuxFigura **tmpAux) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    Quadra *tmpQuad = NULL;
    Torre *tmpTorre = NULL;
    int face, num;
    long int address;
    double x = newAtod(strtok(NULL, " "));
    double y = newAtod(strtok(NULL, " "));
    double width = newAtod(strtok(NULL, " "));
    double height = newAtod(strtok(NULL, " "));
    quadraInsideRectangle(cityIndex, txtOutput, NULL, x, y, width, height, 4);
    semafInsideRectangle(cityIndex, txtOutput, NULL, x, y, width, height, 4);
    hidInsideRectangle(cityIndex, txtOutput, NULL, x, y, width, height, 4);
    torreInsideRectangle(cityIndex, txtOutput, NULL, x, y, width, height, 4);
}

// Armazena os registradores
void getRegistradores(Cidade *cityIndex, char *linha, FILE **txtOutput, int action) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    char *reg = NULL, *cep = NULL, *face = NULL;
    int num;
    Quadra *tmpQuad = NULL, *quadraAux = NULL;
    Estab *tmpEstab = NULL, *estabAux = NULL;
    Moradia *tmpMoradia = NULL;
    Semaforo *tmpSemaf = NULL;
    Hidrante *tmpHid = NULL;
    Torre *tmpTorre = NULL;
    Tipo *tmpTipo = NULL;
    long int address;
    switch (action) {
        case 1: // (m?)
            reg = strtok(NULL, " "); // R
            token = strtok(NULL, " "); // Cpf
            if (getMoradiaAddress(cityIndex, hash((unsigned char *) token), &address, &tmpMoradia, 1)) {
                if (getQuadraAddress(cityIndex, hash((unsigned char *) getMoradiaCep(tmpMoradia)), &address,
                                     &tmpQuad)) {
                    removeFirstChar(&reg);
                    num = newAtoi(reg);
                    putPonto(cityIndex, getQuadraX(tmpQuad), getQuadraY(tmpQuad), num);
                    killQuadra(tmpQuad);
                    killMoradia(tmpMoradia);
                } else {
                    fprintf(*txtOutput, "Quadra não encontrada\n");
                }
                return;
            } else {
                fprintf(*txtOutput, "Pessoa não encontrada\n");
            }
            break;
        case 2: // (e?)
            reg = strtok(NULL, " "); // R
            token = strtok(NULL, " "); // Cep
            if (getQuadraAddress(cityIndex, hash((unsigned char *) getMoradiaCep(tmpMoradia)), &address,
                                 &tmpQuad)) {
                removeFirstChar(&reg);
                num = newAtoi(reg);
                putPonto(cityIndex, getQuadraX(tmpQuad), getQuadraY(tmpQuad), num);
                killQuadra(tmpQuad);
                return;
            } else {
                fprintf(*txtOutput, "Quadra não encontrada\n");
            }
            break;
        case 3: // (g?)
            reg = strtok(NULL, " "); // R
            token = strtok(NULL, " "); // Id
            if (getSemaforoAddress(cityIndex, hash((unsigned char *) token), &address, &tmpSemaf)) {
                removeFirstChar(&reg);
                num = newAtoi(reg);
                putPonto(cityIndex, getSemaforoX(tmpSemaf), getSemaforoY(tmpSemaf), num);
                killSemaforo(tmpSemaf);
                return;
            } else if (getHidranteAddress(cityIndex, hash((unsigned char *) token), &address, &tmpHid)) {
                removeFirstChar(&reg);
                num = newAtoi(reg);
                putPonto(cityIndex, getHidranteX(tmpHid), getHidranteY(tmpHid), num);
                killHidrante(tmpHid);
                return;
            } else if (getTorreAddress(cityIndex, hash((unsigned char *) token), &address, &tmpTorre)) {
                removeFirstChar(&reg);
                num = newAtoi(reg);
                putPonto(cityIndex, getTorreX(tmpTorre), getTorreY(tmpTorre), num);
                killTorre(tmpTorre);
                return;
            } else {
                fprintf(*txtOutput, "id não encontrada\n");
            }
            break;
        case 4: // (e?)
            reg = strtok(NULL, " "); // R
            token = strtok(NULL, " "); // Cep

                removeFirstChar(&reg);
                double x = newAtod(strtok(NULL, " "));
                double y = newAtod(strtok(NULL, " "));
                num = newAtoi(reg);
                putPonto(cityIndex, x, y, num);
            break;
        default:
            break;
    }
}

void rau(Cidade *cityIndex, char *linha, FILE **txtOutput, AuxFigura **tmpAux) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    Carro *tmpCarro;
    long int address;
    // Carro
    token = strtok(NULL, " "); // Placa
    if (getCarroAddress(cityIndex, hash((unsigned char *) token), &address, &tmpCarro)) { // 1 Para busca por cpf
        fprintf(*txtOutput, "Placa = %s  X = %lf  Y = %lf\n", getCarroplaca(tmpCarro), getCarroX(tmpCarro),
                getCarroY(tmpCarro));
        ripcarro(cityIndex, hash((unsigned char *) token));
        killCarro(tmpCarro);
    } else {
        fprintf(*txtOutput, "Pessoa não encontrada\n");
    }

}
