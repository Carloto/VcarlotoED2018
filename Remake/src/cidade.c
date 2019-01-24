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
    int numTorres; // Quantidade de torres
    FILE *estabe; // Arquivo binario de estabelecimentos
    bTree estabeTree; // Arvore contendo os enderecos do arquivo binario
    FILE *tipoestabe; // Arquivo binario de tipos de estabelecimentos
    bTree tipoestabeTree; // Arvore contendo os enderecos do arquivo binario
    FILE *pessoas; // Arquivo binario de pessoa
    bTree pessoasTree; // Arvore contendo os enderecos do arquivo binario
    FILE *moradias; // Arquivo binario de tipos de moradias
    bTree moraCpfTree; // Arvore contendo os enderecos do arquivo binario
    bTree moraCepTree; // Arvore contendo os enderecos do arquivo binario
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
    tmpStruct->numTorres = 0;

    sprintf(name, "%s", "estabelecimento"); // Estabelecimento
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->estabe = openFile(openName, "wb+");
    tmpStruct->estabeTree = btCreate();

    sprintf(name, "%s", "tipoestabelecimento"); // Tipo de estabelecimento
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->tipoestabe = openFile(openName, "wb+");
    tmpStruct->tipoestabeTree = btCreate();

    sprintf(name, "%s", "pessoas"); // Pessoas
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->pessoas = openFile(openName, "wb+");
    tmpStruct->pessoasTree = btCreate();

    sprintf(name, "%s", "moradias"); // Moradias
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->moradias = openFile(openName, "wb+");
    tmpStruct->moraCpfTree = btCreate();
    tmpStruct->moraCepTree = btCreate();

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
    fclose((*cityIndex)->estabe);
    btDestroy((*cityIndex)->estabeTree);
    fclose((*cityIndex)->tipoestabe);
    btDestroy((*cityIndex)->tipoestabeTree);
    fclose((*cityIndex)->pessoas);
    btDestroy((*cityIndex)->pessoasTree);
    fclose((*cityIndex)->moradias);
    btDestroy((*cityIndex)->moraCpfTree);
    btDestroy((*cityIndex)->moraCepTree);
    free(*cityIndex);
}

// Adiciona uma nova estrutura no arquivo binario e na b-tree, a partir do arquivo lido
void newCityShapeFromFile(Cidade *cityIndex, char *inputLine, Color *colorIndex, int typeOfData) {
    Quadra *tmpQuad = NULL;
    Hidrante *tmpHid = NULL;
    Semaforo *tmpSemaf = NULL;
    Torre *tmpTorre = NULL;
    Estab *tmpEstab = NULL;
    Tipo *tmpTipoEstab = NULL;
    Pessoa *tmpPessoa = NULL;
    Moradia *tmpMoradia = NULL;
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
//            printf("\nID = %s", token);
//            printf("   Hash = %lu", hash((unsigned char *) token));
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
            cityIndex->numTorres++;
            break;
        case 5: // Estabelecimento
            tmpEstab = allocEstab();
            token = strtok(NULL, " "); // Cnpj
            setEstabCnpj(tmpEstab, token);
            btInsert(cityIndex->estabeTree, hash((unsigned char *) token), ftell(cityIndex->estabe));
            setEstabCodt(tmpEstab, strtok(NULL, " ")); // Codt
            setEstabCep(tmpEstab, strtok(NULL, " ")); // Cep
            setEstabFace(tmpEstab, strtok(NULL, " ")); // Face
            setEstabNum(tmpEstab, newAtoi(strtok(NULL, " "))); // Num
            setEstabNome(tmpEstab, strtok(NULL, " ")); // Nome
            long int address;
            if (getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(tmpEstab)), &address, &tmpQuad)) {
                switch (getFaceValue(getEstabFace(tmpEstab))) {
                    case 1: // Norte
                        setEstabX(tmpEstab, getQuadraX(tmpQuad) + ((double) getEstabNum(tmpEstab) / 10) * 11); // X
                        setEstabY(tmpEstab, getQuadraY(tmpQuad) + 1); // Y
                        break;
                    case 2: // Sul
                        setEstabX(tmpEstab, getQuadraX(tmpQuad) + ((double) getEstabNum(tmpEstab) / 10) * 11); // X
                        setEstabY(tmpEstab,
                                  getQuadraY(tmpQuad) + getQuadraHeight(tmpQuad) - 11); // Y
                        break;
                    case 3: // Leste
                        setEstabX(tmpEstab, getQuadraX(tmpQuad) + 1); // X
                        setEstabY(tmpEstab, getQuadraY(tmpQuad) +
                                            ((double) getEstabNum(tmpEstab) / 10) * 7); // Y
                        break;
                    case 4: // Oeste
                        setEstabX(tmpEstab, getQuadraX(tmpQuad) + getQuadraWidth(tmpQuad) - 11); // X
                        setEstabY(tmpEstab, getQuadraY(tmpQuad) + ((double) getEstabNum(tmpEstab) / 10) * 7); // Y
                    default:
                        break;
                }
            }
            setEstabStrokeColor(tmpEstab, "black\0");
            setEstabFillColor(tmpEstab, "lightskyblue");
            printToBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
            killEstab(tmpEstab);
            killQuadra(tmpQuad);
            break;
        case 6: // Tipo de estabelecimento
            tmpTipoEstab = allocTipo();
            token = strtok(NULL, " "); // codt
            setTipoCodt(tmpTipoEstab, token);
            btInsert(cityIndex->tipoestabeTree, hash((unsigned char *) token), ftell(cityIndex->tipoestabe));
            setTipodDesc(tmpTipoEstab, strtok(NULL, " "));
            printToBin(&(cityIndex->tipoestabe), getTipoSize(), tmpTipoEstab);
            killTipo(tmpTipoEstab);
            break;
        case 7: // Pessoa
            tmpPessoa = allocPessoa();
            token = strtok(NULL, " "); // Cpf
            setPessoaCpf(tmpPessoa, token);
            btInsert(cityIndex->pessoasTree, hash((unsigned char *) token), ftell(cityIndex->pessoas));
            setPessoaNome(tmpPessoa, strtok(NULL, " ")); // Nome
            setPessoaSobrenome(tmpPessoa, strtok(NULL, " ")); // Sobrenome
            setPessoaSexo(tmpPessoa, strtok(NULL, " ")); // Sexo
            setPessoaNasce(tmpPessoa, strtok(NULL, " ")); // Nascimento
            printToBin(&(cityIndex->pessoas), getPessoaSize(), tmpPessoa);
            killPessoa(tmpPessoa);
            break;
        case 8: // Moradia
            tmpMoradia = allocMoradia();
            token = strtok(NULL, " "); // Cpf
            setMoradiaCpf(tmpMoradia, token);
            btInsert(cityIndex->moraCpfTree, hash((unsigned char *) token), ftell(cityIndex->moradias));
            token = strtok(NULL, " "); // Cep
            setMoradiaCep(tmpMoradia, token);
            btInsert(cityIndex->moraCepTree, hash((unsigned char *) token), ftell(cityIndex->moradias));
            setMoradiaFace(tmpMoradia, strtok(NULL, " ")); // Face
            setMoradiaNum(tmpMoradia, newAtoi(strtok(NULL, " "))); // Num
            setMoradiaComplemento(tmpMoradia, strtok(NULL, " ")); // Complemento
            printToBin(&(cityIndex->moradias), getMoradiaSize(), tmpMoradia);
            killMoradia(tmpMoradia);
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
        case 5: // Estabelecimentos
            return &(cityIndex->estabe);
        case 6: // Pessoa
            return &(cityIndex->pessoas);
        case 7: // Moradia
            return &(cityIndex->moradias);
        default:
            break;
    }
    return NULL;
}

// Cria um vetor de pontos de certa estrutura
Point *torreToPoint(Cidade *cityIndex) {
    Point *listaTorre = allocPoint(cityIndex->numTorres);
    int i = 0;
    Torre *tmpTorre = allocTorre();
    fseek(cityIndex->torres, 0, SEEK_SET);
    while (!feof(cityIndex->torres)) {
        readFromBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
        if (!feof(cityIndex->torres)) {
            if (checkString(getTorreId(tmpTorre))) {
                infoToPoint(&listaTorre, i, hash((unsigned char *) getTorreId(tmpTorre)),
                            getTorreX(tmpTorre), getTorreY(tmpTorre));
                i++;
            }
        }
    }
    killTorre(tmpTorre);
    return listaTorre;
}

// Adiciona uma figura auxiliar a partir da quadra
void addAuxQuadra(Quadra *tmpQuad, AuxFigura **tmpAux, int num, int face, int type) {
    switch (face) {
        case 1: // Norte
            addAux(tmpAux, getQuadraX(tmpQuad) + ((double) num / 10) * 11,
                   getQuadraY(tmpQuad) + 1, 0, 0, type);
            break;
        case 2: // Sul
            addAux(tmpAux, getQuadraX(tmpQuad) + ((double) num / 10) * 11,
                   getQuadraY(tmpQuad) + getQuadraHeight(tmpQuad) - 11, 0, 0, type);
            break;
        case 3: // Leste
            addAux(tmpAux, getQuadraX(tmpQuad) + 1, getQuadraY(tmpQuad) +
                                                    ((double) num / 10) * 7, 0, 0,
                   type);
            break;
        case 4: // Oeste
            addAux(tmpAux, getQuadraX(tmpQuad) + +getQuadraWidth(tmpQuad) - 11, getQuadraY(tmpQuad) +
                                                                                ((double) num /
                                                                                 10) * 7, 0, 0,
                   type);
        default:
            break;
    }
}

// Imprime a pessoa e a moradia para o txt
void pessoaMoradiaTxt(Moradia *tmpMoradia, Pessoa *tmpPessoa, Quadra *tmpQuadra, FILE **txtOutput, int action) {
    fprintf(*txtOutput,
            "Cpf = %s  Nome = %s  %s  Sexo = %s  Nascimento = %s \n", getPessoaCpf(tmpPessoa), getPessoaNome(tmpPessoa),
            getPessoaSobrenome(tmpPessoa), getPessoaSexo(tmpPessoa), getPessoaNasce(tmpPessoa));
    if (action == 1) {
        fprintf(*txtOutput, "Quadra = %s  Num = %d  Face = %s  Complemento = %s  X = %.3lf  Y = %.3lf\n",
                getMoradiaCep(tmpMoradia),
                getMoradiaNum(tmpMoradia), getMoradiaFace(tmpMoradia), getMoradiaComplemento(tmpMoradia),
                getQuadraX(tmpQuadra), getQuadraY(tmpQuadra));
    }
}

// Imprime o estabelecimento e a quadra para o txt
void estabQuadraTxt(Estab *tmpEstab, Tipo *tmpTipo, Quadra *tmpQuad, FILE **txtOutput, int action) {
    fprintf(*txtOutput,
            "Cnpf = %s  Cep = %s  Face = %s  Num = %d\n", getEstabCnpj(tmpEstab), getEstabCep(tmpEstab),
            getEstabFace(tmpEstab), getEstabNum(tmpEstab));
    if (action == 1) {
        fprintf(*txtOutput, "Tiṕo = %s  Descrição = %s  X = %.3lf  Y = %.3lf\n",
                getTipoCodt(tmpTipo),
                getTipoDesc(tmpTipo), getQuadraX(tmpQuad), getQuadraY(tmpQuad));
    }
}

// Retorna o numero de torres
int getNumTorres(Cidade *cityIndex) {
    return cityIndex->numTorres;
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
int getMoradiaAddress(Cidade *cityIndex, unsigned long id, long int *address, Moradia **aux, int action) {
    if (btGetAddress(cityIndex->moraCpfTree, id, address) && action == 1) { // Busca por cpf
        *aux = allocMoradia();
        fseek(cityIndex->moradias, *address, SEEK_SET);
        readFromBin(&(cityIndex->moradias), getMoradiaSize(), *aux);
        return 1;
    } else if (btGetAddress(cityIndex->moraCepTree, id, address) && action == 2) { // Busca por cep
        *aux = allocMoradia();
        fseek(cityIndex->moradias, *address, SEEK_SET);
        readFromBin(&(cityIndex->moradias), getMoradiaSize(), *aux);
        return 1;
    }
    return 0;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getPessoaAddress(Cidade *cityIndex, unsigned long id, long int *address, Pessoa **aux) {
    if (btGetAddress(cityIndex->pessoasTree, id, address)) { // Busca por cpf
        *aux = allocPessoa();
        fseek(cityIndex->pessoas, *address, SEEK_SET);
        readFromBin(&(cityIndex->pessoas), getPessoaSize(), *aux);
        return 1;
    }
    return 0;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getEstabAddress(Cidade *cityIndex, unsigned long id, long int *address, Estab **aux) {
    if (btGetAddress(cityIndex->estabeTree, id, address)) { // Busca por cnpj
        *aux = allocEstab();
        fseek(cityIndex->estabe, *address, SEEK_SET);
        readFromBin(&(cityIndex->estabe), getEstabSize(), *aux);
        return 1;
    }
    return 0;
}

// Retorna 1 e modifica address caso encontre a estrutura
int getTipoAddress(Cidade *cityIndex, unsigned long id, long int *address, Tipo **aux) {
    if (btGetAddress(cityIndex->tipoestabeTree, id, address)) { // Busca por tipo
        *aux = allocTipo();
        fseek(cityIndex->tipoestabe, *address, SEEK_SET);
        readFromBin(&(cityIndex->tipoestabe), getTipoSize(), *aux);
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
    if (action < 3) {
        printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    }
    long int address;
    Quadra *tmpQuad = allocQuadra();
    fseek(cityIndex->quadras, 0, SEEK_SET);
    while (!feof(cityIndex->quadras)) {
        readFromBin(&(cityIndex->quadras), getQuadraSize(), tmpQuad);
        if (!feof(cityIndex->quadras)) {
            if (rectInsideRect(aX, aY, aWidth, aHeigth, getQuadraX(tmpQuad), getQuadraY(tmpQuad),
                               getQuadraWidth(tmpQuad), getQuadraHeight(tmpQuad)) == 1) {
                if (checkString(getQuadraCep(tmpQuad))) {

                    if (action == 3) {  // mr?
                        Moradia *tmpMoradia = NULL;
                        Pessoa *tmpPessoa = NULL;
                        if (getMoradiaAddress(cityIndex, hash((unsigned char *) getQuadraCep(tmpQuad)), &address,
                                              &tmpMoradia,
                                              2)) {   // 2 Para busca por cep
                            if (getPessoaAddress(cityIndex, hash((unsigned char *) getMoradiaCpf(tmpMoradia)), &address,
                                                 &tmpPessoa)) {
                                pessoaMoradiaTxt(tmpMoradia, tmpPessoa, tmpQuad, txtOutput, 1);
                            }
                            killPessoa(tmpPessoa);
                            killMoradia(tmpMoradia);
                        }
                    } else {
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
                            cityIndex->numTorres--;
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
                        case 2: // Dle
                            btDeleteInfo(cityIndex->torreTree, hash((unsigned char *) getTorreId(tmpTorre)), &address);
                            deleteTorre(tmpTorre);
                            fseek(cityIndex->torres, address, SEEK_SET);
                            printToBin(&(cityIndex->torres), getTorreSize(), tmpTorre);
                            cityIndex->numTorres--;
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

    // Estabelecimento
    Estab *tmpEstab = allocEstab();
    fseek(cityIndex->estabe, 0, SEEK_SET);
    printf("\n\n Estabelecimentos \n");
    while (!feof(cityIndex->estabe)) {
        readFromBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
        if (!feof(cityIndex->estabe)) {
            if (checkString(getEstabCnpj(tmpEstab))) {
                printEstab(tmpEstab);
            }
        }
    }
    killEstab(tmpEstab);

    // Tipo de estabelecimento
    Tipo *tmpTipoEstab = allocTipo();
    fseek(cityIndex->tipoestabe, 0, SEEK_SET);
    printf("\n\n Tipos de Estabelecimentos \n");
    while (!feof(cityIndex->tipoestabe)) {
        readFromBin(&(cityIndex->tipoestabe), getTipoSize(), tmpTipoEstab);
        if (!feof(cityIndex->tipoestabe)) {
            if (checkString(getTipoCodt(tmpTipoEstab))) {
                printTipo(tmpTipoEstab);
            }
        }
    }
    killTipo(tmpTipoEstab);

    // Pessoas
    Pessoa *tmpPessoa = allocPessoa();
    fseek(cityIndex->pessoas, 0, SEEK_SET);
    printf("\n\n Pessoas\n");
    while (!feof(cityIndex->pessoas)) {
        readFromBin(&(cityIndex->pessoas), getPessoaSize(), tmpPessoa);
        if (!feof(cityIndex->pessoas)) {
            if (checkString(getPessoaCpf(tmpPessoa))) {
                printPessoa(tmpPessoa);
            }
        }
    }
    killPessoa(tmpPessoa);

    // Moradias
    Moradia *tmpMoradia = allocMoradia();
    fseek(cityIndex->moradias, 0, SEEK_SET);
    printf("\n\n Moradias\n");
    while (!feof(cityIndex->moradias)) {
        readFromBin(&(cityIndex->moradias), getMoradiaSize(), tmpMoradia);
        if (!feof(cityIndex->moradias)) {
            if (checkString(getMoradiaCpf(tmpMoradia))) {
                printMoradia(tmpMoradia);
            }
        }
    }
    killMoradia(tmpMoradia);
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

    // Imprimir estabelecimentos
    Estab *tmpEstab = allocEstab();
    fseek(cityIndex->estabe, 0, SEEK_SET);
    while (!feof(cityIndex->estabe)) {
        readFromBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
        if (!feof(cityIndex->estabe)) {
            if (checkString(getEstabCnpj(tmpEstab))) {
                fprintf(*outputFile,
                        "\t<rect x=\"%lf\" y=\"%lf\" width=\"10\" height=\"10\" ",
                        getEstabX(tmpEstab),
                        getEstabY(tmpEstab));
                fprintf(*outputFile,
                        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" />\n",
                        getEstabStrokeColor(tmpEstab),
                        getEstabFillColor(tmpEstab));
            }
        }
    }
    killEstab(tmpEstab);
}
