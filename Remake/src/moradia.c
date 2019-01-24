// Include
#include "moradia.h"

struct tmpMora { // Moradia
    char cpf[25]; // Cpf do morador
    char cep[50]; // Cep da moradia
    char face[2]; // Face da moradia
    int num; // Numero da moradia
    char complemento[50]; // Complemento da Moradia
};

// Aloca e inicializa uma struct Moradia
Moradia *allocMoradia() {
    Moradia *tmpMoradia = (Moradia *) calloc(1, sizeof(Moradia));
    return tmpMoradia;
}

// Libera a memoria de um unica Moradia
void killMoradia(Moradia *tmpMoradia) {
    if (tmpMoradia != NULL) {
        free(tmpMoradia);
    }
}

// Deleta a Moradia
void deleteMoradia(Moradia *tmpMoradia) {
    sprintf(tmpMoradia->cpf, "%s", "deletado");
}

// Retorna o tamanho de uma Moradia
size_t getMoradiaSize() {
    return sizeof(Moradia);
}

// Set cpf
void setMoradiaCpf(Moradia *tmpMoradia, char tmpCpf[25]) {
    sprintf(tmpMoradia->cpf, "%s", tmpCpf);
}

// Set cep
void setMoradiaCep(Moradia *tmpMoradia, char tmpCep[50]) {
    sprintf(tmpMoradia->cep, "%s", tmpCep);
}

// Set face
void setMoradiaFace(Moradia *tmpMoradia, char tmpFace[2]) {
    sprintf(tmpMoradia->face, "%s", tmpFace);
}

// Set num
void setMoradiaNum(Moradia *tmpMoradia, int tmpNum) {
    tmpMoradia->num = tmpNum;
}

// Set complemento
void setMoradiaComplemento(Moradia *tmpMoradia, char tmpCompl[50]) {
    sprintf(tmpMoradia->complemento, "%s", tmpCompl);
}

// Get cpf
char *getMoradiaCpf(Moradia *tmpMoradia) {
    return tmpMoradia->cpf;
}

// Get cep
char *getMoradiaCep(Moradia *tmpMoradia) {
    return tmpMoradia->cep;
}

// Get face
char *getMoradiaFace(Moradia *tmpMoradia) {
    return tmpMoradia->face;
}

// get num
int getMoradiaNum(Moradia *tmpMoradia) {
    return tmpMoradia->num;
}

// Get complemento
char *getMoradiaComplemento(Moradia *tmpMoradia) {
    return tmpMoradia->complemento;
}

// Imprime as informações do Retangulo
void printMoradia(Moradia *tmpMoradia) {
    printf("\ncpf = |%s|", tmpMoradia->cpf);
    printf("  cep = |%s|", tmpMoradia->cep);
    printf("  face = |%s|", tmpMoradia->face);
    printf("  num = |%d|", tmpMoradia->num);
    printf("  complemento = |%s|", tmpMoradia->complemento);
}
