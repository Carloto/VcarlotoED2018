// Include
#include "estabelecimento.h"

struct tmpEstab { // Estabelecimento
    char cnpj[50]; // Id da Estab
    char codt[25]; // Endereço do tipo
    char cep[50]; // Cep da quadra
    char face[1]; // Face da quadra
    int num; // Numero do endereço
    char nome[50]; // Nome do estabelecimento
    double xCoord; // X do canto superior esquerdo
    double yCoord; // Y do canto superior esquerdo
    char fillColor[50]; // Cor interior
    char strokeColor[50]; // Cor da borda
};

// Aloca e inicializa uma struct Estab
Estab *allocEstab() {
    Estab *tmpEstab = (Estab *) calloc(1, sizeof(Estab));
    return tmpEstab;
}

// Libera a memoria de uma unica Estab
void killEstab(Estab *tmpEstab) {
    if (tmpEstab != NULL) {
        free(tmpEstab);
    }
}

// Deleta a Estab
void deleteEstab(Estab *tmpEstab) {
    sprintf(tmpEstab->cnpj, "%s", "deletado");
}

// Retorna o tamanho de uma Estab
size_t getEstabSize() {
    return sizeof(Estab);
}

// Set cnpj
void setEstabCnpj(Estab *tmpEstab, char tmpCnpj[50]) {
    sprintf(tmpEstab->cnpj, "%s", tmpCnpj);
}

// Set codt
void setEstabCodt(Estab *tmpEstab, char tmpCodt[25]) {
    sprintf(tmpEstab->codt, "%s", tmpCodt);
}

// Set cep
void setEstabCep(Estab *tmpEstab, char tmpCep[50]) {
    sprintf(tmpEstab->cep, "%s", tmpCep);
}

// Set face
void setEstabFace(Estab *tmpEstab, char tmpFace[2]) {
    sprintf(tmpEstab->face, "%s", tmpFace);
}

// Set num
void setEstabNum(Estab *tmpEstab, int num) {
    tmpEstab->num = num;
}

// Set nome
void setEstabNome(Estab *tmpEstab, char tmpNome[50]) {
    sprintf(tmpEstab->nome, "%s", tmpNome);
}

// Set X
void setEstabX(Estab *tmpEstab, double tmpX) {
    tmpEstab->xCoord = tmpX;
}

// Set Y
void setEstabY(Estab *tmpEstab, double tmpY) {
    tmpEstab->yCoord = tmpY;
}

// Set fillColor
void setEstabFillColor(Estab *tmpEstab, char tmpFillColor[50]) {
    sprintf(tmpEstab->fillColor, "%s", tmpFillColor);
}

// Set strokeColor
void setEstabStrokeColor(Estab *tmpEstab, char tmpStrokeColor[50]) {
    sprintf(tmpEstab->strokeColor, "%s", tmpStrokeColor);
}

// Get cnpj
char *getEstabCnpj(Estab *tmpEstab) {
    return tmpEstab->cnpj;
}

// Get codt
char *getEstabCodt(Estab *tmpEstab) {
    return tmpEstab->codt;
}

// Get cep
char *getEstabCep(Estab *tmpEstab) {
    return tmpEstab->cep;
}

// Get face
char *getEstabFace(Estab *tmpEstab) {
    return tmpEstab->face;
}

// Get num
int getEstabNum(Estab *tmpEstab) {
    return tmpEstab->num;
}

// Get cep
char *getEstabNome(Estab *tmpEstab) {
    return tmpEstab->nome;
}

// Get X
double getEstabX(Estab *tmpEstab) {
    return tmpEstab->xCoord;
}

// Get Y
double getEstabY(Estab *tmpEstab) {
    return tmpEstab->yCoord;
}

// Get fillColor
char *getEstabFillColor(Estab *tmpEstab) {
    return tmpEstab->fillColor;
}

// Get strokeColor
char *getEstabStrokeColor(Estab *tmpEstab) {
    return tmpEstab->strokeColor;
}

// Imprime as informações do Retangulo
void printEstab(Estab*tmpEstab) {
    printf("\ncnpj = |%s|", tmpEstab->cnpj);
    printf("  codt = |%s|", tmpEstab->codt);
    printf("  cep = |%s|", tmpEstab->cep);
    printf("  face = |%s|", tmpEstab->face);
    printf("  num = |%d|", tmpEstab->num);
    printf("  nome = |%s|", tmpEstab->nome);
    printf("  x = |%.3lf|", tmpEstab->xCoord);
    printf("  y = |%.3lf|", tmpEstab->yCoord);
    printf("  fill color = |%s|\n", tmpEstab->fillColor);
    printf("  stroke color = |%s|", tmpEstab->strokeColor);
}
