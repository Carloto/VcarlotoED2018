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
    FILE *carros; // Arquivo binario de carro
    bTree carrosTree; // Arvore contendo os enderecos do arquivo binario
    FILE *moradias; // Arquivo binario de tipos de moradias
    bTree moraCpfTree; // Arvore contendo os enderecos do arquivo binario
    bTree moraCepTree; // Arvore contendo os enderecos do arquivo binario
    FILE *vias; // Arquivo binario de .via
    float **matrizTempo;
    float **matrizDist;
    Grafo *grafo;
    ponto pontos[10];
};

void Best_Caminho(char *line, Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput) {
    char *token; //procura o melhor caminho a ser tomado
    char *info;
    int indexSrc;
    int indexDest;
    char *cor = NULL;
    int size = Tamanho(cityIndex->grafo->verts);
    int *caminho = (int *) malloc(sizeof(int) * size);
    char *svgfinal = NULL;
    token = strtok(line, " ");
    token = strtok(NULL, "R");
    info = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(info, token);
    token = strtok(NULL, " ");
    indexSrc = atoi(token);
    token = strtok(NULL, " ");
    if (token[1] == '1') {
        if (token[2] == '0') {
            indexDest = 10;
        } else indexDest = 1;
    } else {
        indexDest = token[1] - '0';
    }
    token = strtok(NULL, "\n");
    if (token != NULL) {
        cor = (char *) malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(cor, token);
    }
    token = strtok(info, " ");
    int picOrText;
    char *sufixo = NULL;
    int DorT;
    if (token[0] == 't') {
        picOrText = 1;
        token = strtok(NULL, " ");
        if (token[0] == 'T') {
            DorT = 1;
        } else {
            DorT = 0;
        }
    } else if (token[0] == 'p') {
        picOrText = 0;
        token = strtok(NULL, " ");
        sufixo = (char *) malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(sufixo, token);
        token = strtok(NULL, " ");
        if (token[0] == 'T') {
            DorT = 1;
        } else {
            DorT = 0;
        }
    }
    Vertice *vert1 = NULL;
    vert1 = Vertice_Perto_X_Y(cityIndex->grafo->verts, cityIndex->pontos[indexSrc]);
    Vertice *vert2 = NULL;
    vert2 = Vertice_Perto_X_Y(cityIndex->grafo->verts, cityIndex->pontos[indexDest]);
    if (DorT == 1) {
        caminho = Dijkstra(vert1->numericID, vert2->numericID, cityIndex->matrizTempo, size, caminho);
    }
    if (DorT == 0) {
        caminho = Dijkstra(vert1->numericID, vert2->numericID, cityIndex->matrizDist, size, caminho);
    }
    if (picOrText == 1) {
        Repr_Caminho(cityIndex->grafo, caminho, size, *txtOutput);
    } else if (picOrText == 0) {
        fprintf(*svgOutput, "<svg>\n");
        fprintf(*svgOutput, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:3\" />\n",
                cityIndex->pontos[indexSrc].x, cityIndex->pontos[indexSrc].y, vert1->Ponto.x, vert1->Ponto.y, cor);
        fprintf(*svgOutput, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:3\" />\n",
                cityIndex->pontos[indexDest].x, cityIndex->pontos[indexDest].y, vert2->Ponto.x, vert2->Ponto.y, cor);
    }
}

void
Best_Direcao_Caminho(char *line, Cidade *cityIndex, FILE **txtOutput, FILE **svgOutput) {
    int size = Tamanho(cityIndex->grafo->verts);
    char *token;
    char *info;
    int *indices;
    int qtd;
    char *cor1 = NULL;
    char *cor2 = NULL;
    char *cor;
    int *caminho = (int *) malloc(sizeof(int) * size);
    char *svgfinal;
    token = strtok(line, " ");
    token = strtok(NULL, "R");
    info = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(info, token);
    qtd = info[strlen(info) - 2] - '0';
    token = strtok(NULL, " ");
    indices = (int *) malloc(sizeof(int) * qtd);
    indices[0] = atoi(token);
    for (int i = 1; i < qtd; i++) {
        token = strtok(NULL, " ");
        indices[i] = token[strlen(token) - 1] - '0';
    }
    token = strtok(NULL, " ");
    cor1 = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(cor1, token);
    token = strtok(NULL, " ");
    cor2 = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(cor2, token);
    token = strtok(info, " ");
    int picOrText;
    char *sufixo = NULL;
    int DorT;
    if (token[0] == 't') {
        picOrText = 1;
        token = strtok(NULL, " ");
        if (token[0] == 'T') {
            DorT = 1;
        } else {
            DorT = 0;
        }
    } else if (token[0] == 'p') {
        picOrText = 0;
        token = strtok(NULL, " ");
        sufixo = (char *) malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(sufixo, token);
        token = strtok(NULL, " ");
        if (token[0] == 'T') {
            DorT = 1;
        } else {
            DorT = 0;
        }
    }
    if (DorT == 1) {
        for (int i = 0; i < qtd - 1; i++) {
            int index1, index2;
            index1 = indices[i];
            index2 = indices[i + 1];
            Vertice *vert1 = Vertice_Perto_X_Y(cityIndex->grafo->verts, cityIndex->pontos[index1]);
            Vertice *vert2 = Vertice_Perto_X_Y(cityIndex->grafo->verts, cityIndex->pontos[index2]);
            caminho = Dijkstra(vert1->numericID, vert2->numericID, cityIndex->matrizTempo, size, caminho);
            if (picOrText == 0) {
                if (i % 2 == 0) {
                    cor = (char *) malloc(sizeof(char) * strlen(cor1));
                    strcpy(cor, cor1);
                } else if (i % 2 == 1) {
                    cor = (char *) malloc(sizeof(char) * strlen(cor2));
                    strcpy(cor, cor2);
                }
                fprintf(*svgOutput,
                        "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:3\" />\n",
                        cityIndex->pontos[index1].x, cityIndex->pontos[index1].y, vert1->Ponto.x, vert1->Ponto.y, cor);
                fprintf(*svgOutput,
                        "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:3\" />\n",
                        cityIndex->pontos[index2].x, cityIndex->pontos[index2].y, vert2->Ponto.x, vert2->Ponto.y, cor);
            } else if (picOrText == 1) {
                Repr_Caminho(cityIndex->grafo, caminho, size, *txtOutput);
            }
        }
    } else if (DorT == 0) {
        for (int i = 0; i < qtd - 1; i++) {
            int index1, index2;
            index1 = indices[i];
            index2 = indices[i + 1];
            Vertice *vert1 = Vertice_Perto_X_Y(cityIndex->grafo->verts, cityIndex->pontos[index1]);
            Vertice *vert2 = Vertice_Perto_X_Y(cityIndex->grafo->verts, cityIndex->pontos[index2]);
            caminho = Dijkstra(vert1->numericID, vert2->numericID, cityIndex->matrizDist, size, caminho);
            if (picOrText == 0) {
                if (i % 2 == 0) {
                    cor = (char *) malloc(sizeof(char) * strlen(cor1));
                    strcpy(cor, cor1);
                } else if (i % 2 == 1) {
                    cor = (char *) malloc(sizeof(char) * strlen(cor2));
                    strcpy(cor, cor2);
                }
                fprintf(*svgOutput,
                        "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:3\" />\n",
                        cityIndex->pontos[index1].x, cityIndex->pontos[index1].y, vert1->Ponto.x, vert1->Ponto.y, cor);
                fprintf(*svgOutput,
                        "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:3\" />\n",
                        cityIndex->pontos[index2].x, cityIndex->pontos[index2].y, vert2->Ponto.x, vert2->Ponto.y, cor);
            }
            if (picOrText == 1) {
                Repr_Caminho(cityIndex->grafo, caminho, size, *txtOutput);
            }
        }
    }
}

Vertice *Vertice_Index(List *verts, int index) { //index do vertice
    Vertice *vertFinal = NULL;
    Node *node = verts->head;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        if (vert->numericID == index) {
            vertFinal = vert;
        }
        node = node->next;
    }
    return vertFinal;
}


void Repr_Caminho(Grafo *grafo, int *caminho, int size, FILE *arqtxt) { //printa o caminho a ser seguido

    if (arqtxt != NULL) {
        int index1, index2;
        Vertice *vert1, *vert2;

        for (int i = 0; i < size - 1; i++) {
            index1 = caminho[i];
            i++;
            index2 = caminho[i];

            if (index1 != index2) {
                vert1 = Vertice_Index(grafo->verts, index1);
                vert2 = Vertice_Index(grafo->verts, index2);
                if (vert1 != NULL && vert2 != NULL) {
                    Aresta *aresta = ArestaFinal(vert1, vert2);
                    if (aresta != NULL) {
                        fprintf(arqtxt, "siga pela rua %s\n", aresta->nome);
                    }
                }
            }
        }
    }
}

Vertice *Vertice_Perto_X_Y(List *verts, ponto data) { //acha o vertice mais proximo em X e Y
    Node *node = verts->head;
    Vertice *vertFinal;
    float min = 999999;
    float d;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        d = sqrt(pow(vert->Ponto.x - data.x, 2) + pow(vert->Ponto.y - data.y, 2));
        Node *nodeAresta = vert->arestas->head;
        while (nodeAresta != NULL) {
            Aresta *aresta = (Aresta *) nodeAresta->data;
            if (d < min && (strlen(aresta->lesq) > 3 && strlen(aresta->ldir) > 3)) {
                vertFinal = vert;
                min = d;
            }
            nodeAresta = nodeAresta->next;
        }
        node = node->next;
    }
    return vertFinal;
}

int *Dijkstra(int indexSrc, int indexDest, float **matriz, int size, int *caminho) {
    int i = 0;
    int j = 0;
    int u = 0;
    int cont = 0;
    int pesos[size];
    caminho = (int *) malloc(sizeof(int) * (size + 1));
    int visitados[size];
    for (i = 0; i < size; i++) {
        pesos[i] = 9999;
        caminho[i] = -1;
        visitados[i] = 0;
    }
    pesos[indexSrc] = 0;
    for (cont = 0; cont < size - 1; cont++) {
        u = Menor_Distancia(pesos, visitados, size);
        visitados[u] = 1;
        for (j = 0; j < size; j++) {
            if ((visitados[j] == 0) && (matriz[u][j] != -1) && (pesos[u] != 9999) &&
                (pesos[u] + matriz[u][j] < pesos[j])) {
                pesos[j] = matriz[u][j] + pesos[u];
                caminho[j] = u;
            }
        }
    }
    int *Final_Path = (int *) malloc(sizeof(int) * size);
    for (int z = 0; z < size; z++) {
        Final_Path[z] = -1;
    }
    int z = 1;
    Final_Path[0] = indexDest;
    int indexSearch = caminho[indexDest];
    while (indexSearch != 0) {
        Final_Path[z] = indexSearch;
        indexSearch = caminho[indexSearch];
        z++;
    }
    return Final_Path;
}

int Menor_Distancia(int *pesos, int *visitados, int size) { //menor distancia
    int i = 0;
    int min = 9999;
    int indexmin = -1;
    for (i = 0; i < size; i++) {
        if ((visitados[i] == 0) && (pesos[i] <= min)) {
            min = pesos[i];
            indexmin = i;
        }
    }
    return indexmin;
}

void putPonto(Cidade *cityIndex, float x, float y, int i) {
    cityIndex->pontos[i].x = x;
    cityIndex->pontos[i].y = y;
}

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

    sprintf(name, "%s", "carros"); // Pessoas
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->carros = openFile(openName, "wb+");
    tmpStruct->carrosTree = btCreate();

    sprintf(name, "%s", "moradias"); // Moradias
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->moradias = openFile(openName, "wb+");
    tmpStruct->moraCpfTree = btCreate();
    tmpStruct->moraCepTree = btCreate();

    sprintf(name, "%s", "vias"); // Vias
    strcatFileName(&openName, getFullPathBd(source), &name, ".bin\0");
    tmpStruct->vias = openFile(openName, "wb+");

    tmpStruct->matrizTempo = NULL;
    tmpStruct->matrizDist = NULL;
    tmpStruct->grafo = Novo_Grafo();

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
    fclose((*cityIndex)->carros);
    btDestroy((*cityIndex)->carrosTree);
    fclose((*cityIndex)->moradias);
    btDestroy((*cityIndex)->moraCpfTree);
    btDestroy((*cityIndex)->moraCepTree);
    fclose((*cityIndex)->vias);
    free(*cityIndex);
}

// Guarda as vias no arquivo binario
void viasToBin(Cidade *cityIndex, char linha[200]) {
    printToBin(&(cityIndex->vias), sizeof(char[200]), linha);
}

// Le as vias no arquivo bin
void readVias(Cidade *cityIndex, FILE **svgOutput) {
    char linha[200], line_full[200], *token;
    fseek(cityIndex->vias, 0, SEEK_SET);
    int vertCont = 0;
    while (!feof(cityIndex->vias)) {
        readFromBin(&(cityIndex->vias), sizeof(char[200]), linha);
        if (!feof(cityIndex->vias)) {
            strcpy(line_full, linha);
            token = strtok(linha, " ");
            if (strcmp(token, "v") == 0 || strcmp(token, "v\n") == 0) {
                Adicao_Vertices(cityIndex->grafo, line_full, vertCont);
                vertCont++;
            }
            if (strcmp(token, "e") == 0 || strcmp(token, "e\n") == 0) {
                Adicao_Arestas(cityIndex->grafo, line_full);
            }
        }

        Insere_Variaveis_Vertices(cityIndex->grafo);
        cityIndex->matrizTempo = Insere_Var_Matriz((cityIndex->grafo)->verts, cityIndex->matrizTempo);
        cityIndex->matrizDist = Insere_Distancias_Mat((cityIndex->grafo)->verts, cityIndex->matrizDist);
    }
    print_Vertices(svgOutput, cityIndex->grafo);
}

void print_Vertices(FILE **f, Grafo *grafo) {
    List *verts = grafo->verts;
    Node *node = verts->head;
    while (node != NULL) {
        Vertice *vert = (Vertice *) node->data;
        fprintf(*f, "<text x=\"%f\" y=\"%f\" fill=\"black\" >%d </text>\n", vert->Ponto.x, vert->Ponto.y,
                vert->numericID);
        node = node->next;
    }
}

void Adicao_Vertices(Grafo *grafo, char *line, int numericID) { //adiciona vertices
    char *token;
    char *id;
    float x;
    float y;
    token = strtok(line, " ");
    token = strtok(NULL, " ");
    id = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(id, token);
    token = strtok(NULL, " ");
    x = atol(token);
    token = strtok(NULL, " ");
    y = atol(token);
    Coloca_Vertices(id, x, y, grafo, numericID);
}

void Adicao_Arestas(Grafo *grafo, char *line) { //adiciona arestas
    char *token;
    char *src;
    char *dest;
    char *ldir;
    char *lesq;
    float cmp;
    float vm;
    char *nome;
    token = strtok(line, " ");
    token = strtok(NULL, " ");
    src = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(src, token);
    token = strtok(NULL, " ");
    dest = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(dest, token);
    token = strtok(NULL, " ");
    ldir = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(ldir, token);
    token = strtok(NULL, " ");
    lesq = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(lesq, token);
    token = strtok(NULL, " ");
    cmp = atol(token);
    token = strtok(NULL, " ");
    vm = atol(token);
    token = strtok(NULL, " ");
    nome = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(nome, token);
    Coloca_Aresta(src, dest, ldir, lesq, cmp, vm, nome, grafo);
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
    Carro *tmpCarro = NULL;
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
        case 9: // Carro
            tmpCarro = allocCarro();
            token = strtok(NULL, " "); // Placa
            setCarroPlaca(tmpCarro, token);
            btInsert(cityIndex->carrosTree, hash((unsigned char *) token), ftell(cityIndex->carros));
            setCarroX(tmpCarro, newAtod(strtok(NULL, " ")));
            setCarroY(tmpCarro, newAtod(strtok(NULL, " ")));
            setCarroWidth(tmpCarro, newAtod(strtok(NULL, " ")));
            setCarroHeight(tmpCarro, newAtod(strtok(NULL, " ")));
            printToBin(&(cityIndex->carros), getCarroSize(), tmpCarro);
            killCarro(tmpCarro);
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

// Encontra o hidrante mais proximo e reporta a distancia
void closestHidrante(Cidade *cityIndex, FILE **outputTxt, unsigned long id, double x, double y, int action,
                     AuxFigura **tmpAux) {

    if (action == 2) {
        // Hidrante
        Torre *tmpTorre = NULL;
        Hidrante *tmpHid = allocHidrante();
        Hidrante *auxHid = NULL;
        unsigned long id2 = 0;
        long int address;
        double distance = DBL_MAX;
        fseek(cityIndex->hidrantes, 0, SEEK_SET);
        while (!feof(cityIndex->hidrantes)) {
            readFromBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
            if (!feof(cityIndex->hidrantes)) {
                if (checkString(getHidranteId(tmpHid))) {
                    if (findDistance(x, y, getHidranteX(tmpHid), getHidranteY(tmpHid)) < distance) {
                        distance = findDistance(x, y, getHidranteX(tmpHid), getHidranteY(tmpHid));
                        id2 = hash((unsigned char *) getHidranteId(tmpHid));
                    }
                }
            }
        }
        killHidrante(tmpHid);
        getTorreAddress(cityIndex, id, &address, &tmpTorre);
        getHidranteAddress(cityIndex, id2, &address, &auxHid);
        addAux(tmpAux, x, y, getHidranteX(auxHid), getHidranteY(auxHid), 6);
        fprintf(*outputTxt, "Distancia = %lf\n", distance);
        torreTxt(tmpTorre, outputTxt);
        hidranteTxt(auxHid, outputTxt);
        killTorre(tmpTorre);
        killHidrante(auxHid);
        return;
    }

    // Hidrante
    Hidrante *tmpHid = allocHidrante();
    Hidrante *auxHid = NULL;
    unsigned long id2 = 0;
    long int address;
    double distance = DBL_MAX;
    fseek(cityIndex->hidrantes, 0, SEEK_SET);
    while (!feof(cityIndex->hidrantes)) {
        readFromBin(&(cityIndex->hidrantes), getHidranteSize(), tmpHid);
        if (!feof(cityIndex->hidrantes)) {
            if (checkString(getHidranteId(tmpHid))) {
                if (findDistance(x, y, getHidranteX(tmpHid), getHidranteY(tmpHid)) < distance) {
                    distance = findDistance(x, y, getHidranteX(tmpHid), getHidranteY(tmpHid));
                    id2 = hash((unsigned char *) getHidranteId(tmpHid));
                }
            }
        }
    }
    killHidrante(tmpHid);
    getHidranteAddress(cityIndex, id2, &address, &auxHid);
    addAux(tmpAux, x, y, getHidranteX(auxHid), getHidranteY(auxHid), 5);
    fprintf(*outputTxt, "Distancia = %lf\n", distance);
    hidranteTxt(auxHid, outputTxt);
    killHidrante(auxHid);
}

// Imprime o hidrante no txt
void hidranteTxt(Hidrante *tmpHid, FILE **outputTxt) {
    fprintf(*outputTxt, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
            getHidranteId(tmpHid), getHidranteX(tmpHid),
            getHidranteY(tmpHid),
            getHidranteStrokeColor(tmpHid), getHidranteFillColor(tmpHid));
}

// Muda a pessoa de endereço
void mudaPessoa(Cidade *cityIndex, char cpf[25], char cep[50], char face[2], char complemento[50], int num) {
    Moradia *tmpMoradia = allocMoradia();
    long int address;
    readFromBin(&(cityIndex->moradias), getMoradiaSize(), tmpMoradia);
    btGetAddress(cityIndex->moraCpfTree, hash((unsigned char *) cpf), &address);
    setMoradiaCep(tmpMoradia, cep);
    setMoradiaComplemento(tmpMoradia, complemento);
    setMoradiaFace(tmpMoradia, face);
    setMoradiaNum(tmpMoradia, num);
    fseek(cityIndex->moradias, address, SEEK_SET);
    printToBin(&(cityIndex->moradias), getMoradiaSize(), tmpMoradia);
    killMoradia(tmpMoradia);
}

// Muda o estabelecimento de endereco
void mudaEstab(Cidade *cityIndex, char cnpj[50], char cep[50], char face[2], int num) {
    Estab *tmpEstab = allocEstab();
    long int address;
    readFromBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
    btGetAddress(cityIndex->estabeTree, hash((unsigned char *) cnpj), &address);
    setEstabCep(tmpEstab, cep);
    setEstabFace(tmpEstab, face);
    setEstabNum(tmpEstab, num);
    fseek(cityIndex->estabe, address, SEEK_SET);
    printToBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
    killEstab(tmpEstab);
}

// Imprime a torre no txt
void torreTxt(Torre *tmpTorre, FILE **outputTxt) {
    fprintf(*outputTxt, "Id = %s  X = %lf  Y = %lf  Stroke = %s  Fill = %s\n",
            getTorreId(tmpTorre), getTorreX(tmpTorre),
            getTorreY(tmpTorre),
            getTorreStrokeColor(tmpTorre), getTorreFillColor(tmpTorre));
}

// Declara um estabelecimento fechado deleta suas informações
void ripEstab(Cidade *cityIndex, unsigned long id) {
    // establecimento
    long int address;
    Estab *tmpEstab = allocEstab();
    readFromBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
    btDeleteInfo(cityIndex->estabeTree, id, &address);
    deleteEstab(tmpEstab);
    fseek(cityIndex->estabe, address, SEEK_SET);
    printToBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
    killEstab(tmpEstab);
}

// Declara uma pessoa morta e deleta suas informações
void ripPessoa(Cidade *cityIndex, unsigned long id) {
    // Pessoa
    long int address;
    Pessoa *tmpPessoa = allocPessoa();
    btDeleteInfo(cityIndex->pessoasTree, id, &address);
    readFromBin(&(cityIndex->pessoas), getPessoaSize(), tmpPessoa);
    deletePessoa(tmpPessoa);
    fseek(cityIndex->pessoas, address, SEEK_SET);
    printToBin(&(cityIndex->pessoas), getPessoaSize(), tmpPessoa);
    killPessoa(tmpPessoa);
    // Moradia
    Moradia *tmpMoradia = allocMoradia();
    btDeleteInfo(cityIndex->moraCpfTree, id, &address);
    readFromBin(&(cityIndex->moradias), getMoradiaSize(), tmpMoradia);
    unsigned long id2 = hash((unsigned char *) getMoradiaCep(tmpMoradia));
    deleteMoradia(tmpMoradia);
    fseek(cityIndex->moradias, address, SEEK_SET);
    printToBin(&(cityIndex->moradias), getMoradiaSize(), tmpMoradia);
    btDeleteInfo(cityIndex->moraCepTree, id2, &address);
    killMoradia(tmpMoradia);
}

// Lista os estabelecimentos dentro de certa quadra
void reportEstabCep(Cidade *cityIndex, unsigned long id, FILE **txtOutput, int action) {
    // Estabelecimento
    Estab *tmpEstab = allocEstab();
    Quadra *tmpQuad = NULL;
    Tipo *tmpTipo = NULL;
    long int address;
    unsigned long id2;
    fseek(cityIndex->estabe, 0, SEEK_SET);
    while (!feof(cityIndex->estabe)) {
        readFromBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
        if (!feof(cityIndex->estabe)) {
            if (checkString(getEstabCnpj(tmpEstab))) {
                if (action == 2) {
                    id2 = hash((unsigned char *) getEstabCodt(tmpEstab));
                } else {
                    id2 = hash((unsigned char *) getEstabCep(tmpEstab));
                }
                if (id2 == id) {
                    getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(tmpEstab)), &address, &tmpQuad);
                    getTipoAddress(cityIndex, hash((unsigned char *) getEstabCodt(tmpEstab)), &address, &tmpTipo);
                    estabQuadraTxt(tmpEstab, tmpTipo, tmpQuad, txtOutput, action);
                    killQuadra(tmpQuad);
                    killTipo(tmpTipo);
                }
            }
        }
    }
    killEstab(tmpEstab);
}

// Lista os estabelecimentos dentro de certo perimetro
void
reportEstabInside(Cidade *cityIndex, unsigned long id, FILE **txtOutput, int action, double x, double y, double width,
                  double height) {
    // Estabelecimento
    Estab *tmpEstab = allocEstab();
    Quadra *tmpQuad = NULL;
    Tipo *tmpTipo = NULL;
    long int address;
    unsigned long id2;
    fseek(cityIndex->estabe, 0, SEEK_SET);
    while (!feof(cityIndex->estabe)) {
        readFromBin(&(cityIndex->estabe), getEstabSize(), tmpEstab);
        if (!feof(cityIndex->estabe)) {
            if (checkString(getEstabCnpj(tmpEstab))) {
                if (action == 5) {
                    id2 = id;
                } else if (action == 2) {
                    id2 = hash((unsigned char *) getEstabCodt(tmpEstab));
                } else {
                    id2 = hash((unsigned char *) getEstabCep(tmpEstab));
                }
                if (id2 == id) {
                    getQuadraAddress(cityIndex, hash((unsigned char *) getEstabCep(tmpEstab)), &address, &tmpQuad);
                    if (pointInsideRectangle(getQuadraX(tmpQuad), getQuadraY(tmpQuad), x, y, width, height) == 1) {
                        getTipoAddress(cityIndex, hash((unsigned char *) getEstabCodt(tmpEstab)), &address, &tmpTipo);
                        estabQuadraTxt(tmpEstab, tmpTipo, tmpQuad, txtOutput, 1);
                        killTipo(tmpTipo);
                    }
                    killQuadra(tmpQuad);
                }
            }
        }
    }
    killEstab(tmpEstab);
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
            addAux(tmpAux, getQuadraX(tmpQuad) + getQuadraWidth(tmpQuad) - 11, getQuadraY(tmpQuad) +
                                                                               ((double) num /
                                                                                10) * 7, 0, 0,
                   type);
        default:
            break;
    }
}

// Imprime a pessoa e a moradia para o txt
void pessoaMoradiaTxt(Moradia *tmpMoradia, Pessoa *tmpPessoa, Quadra *tmpQuadra, FILE **txtOutput, int action) {
    if (action == 4) {
        fprintf(*txtOutput,
                "RIP : %s %s do sexo  %s, nascido em  %s \n", getPessoaNome(tmpPessoa),
                getPessoaSobrenome(tmpPessoa), getPessoaSexo(tmpPessoa), getPessoaNasce(tmpPessoa));
        fprintf(*txtOutput,
                "Residia no cep %s de num %d de face %s \n", getMoradiaCep(tmpMoradia), getMoradiaNum(tmpMoradia),
                getMoradiaFace(tmpMoradia));
        return;
    }
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
            "Cnpj = %s  Nome = %s  Cep = %s  Face = %s  Num = %d\n", getEstabCnpj(tmpEstab), getEstabNome(tmpEstab),
            getEstabCep(tmpEstab),
            getEstabFace(tmpEstab), getEstabNum(tmpEstab));
    if (action == 1) {
        fprintf(*txtOutput, "Tipo = %s  Descrição = %s  X = %.3lf  Y = %.3lf\n",
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
int getCarroAddress(Cidade *cityIndex, unsigned long id, long int *address, Carro**aux) {
    if (btGetAddress(cityIndex->carrosTree, id, address)) { // Busca por placa
        *aux = allocCarro();
        fseek(cityIndex->carros, *address, SEEK_SET);
        readFromBin(&(cityIndex->carros), getCarroSize(), *aux);
        return 1;
    }
    return 0;
}

// Declara uma pessoa morta e deleta suas informações
void ripcarro(Cidade *cityIndex, unsigned long id) {
    // carro
    long int address;
    Carro *tmpCarro = allocCarro();
    btDeleteInfo(cityIndex->carrosTree, id, &address);
    readFromBin(&(cityIndex->carros), getCarroSize(), tmpCarro);
    deleteCarro(tmpCarro);
    fseek(cityIndex->carros, address, SEEK_SET);
    printToBin(&(cityIndex->carros), getCarroSize(), tmpCarro);
    killCarro(tmpCarro);
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
                            case 4:
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
    if (action < 3) {
        printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    }
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
                        case 4:
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
    if (action < 3) {
        printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    }
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
                        case 4:
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
    if (action < 3) {
        printDashRectangle(svgOutput, aX, aY, aWidth, aHeigth);
    }
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
                        case 4:
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

    // Imprimir carros
    Carro *tmpCarro = allocCarro();
    fseek(cityIndex->carros, 0, SEEK_SET);
    while (!feof(cityIndex->carros)) {
        readFromBin(&(cityIndex->carros), getCarroSize(), tmpCarro);
        if (!feof(cityIndex->carros)) {
            if (checkString(getCarroplaca(tmpCarro))) {
                fprintf(*outputFile,
                        "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" ",
                        getCarroX(tmpCarro),
                        getCarroY(tmpCarro),
                        getCarroWidth(tmpCarro),
                        getCarroHeight(tmpCarro));
                fprintf(*outputFile,
                        "stroke=\"%s\" fill=\"%s\" style=\"stroke-width: 3;\" />\n", "black", "white");
                fprintf(*outputFile,
                        "\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" stroke=\"black\" text-anchor=\"middle\" alignment-baseline=\"central\" style=\"stroke-width: 0.5;\" >%s</text>\n",
                        (getCarroWidth(tmpCarro) / 2) + getCarroX(tmpCarro),
                        (getCarroHeight(tmpCarro) / 2) + getCarroY(tmpCarro),
                        getCarroplaca(tmpCarro));
            }
        }
    }
    killCarro(tmpCarro);

}
