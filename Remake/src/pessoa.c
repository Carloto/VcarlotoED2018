// Include
#include "pessoa.h"

struct tmpPess { // Pessoa
    char cpf[25]; // Cpf da Pessoa
    char nome[50]; // Nome da Pessoa
    char sobrenome[50]; // Sobrenome da Pessoa
    char sexo[2]; // Sexo da Pessoa
    char nasce[25]; // Data de nascimento da Pessoa
};

// Aloca e inicializa uma struct Pessoa
Pessoa *allocPessoa() {
    Pessoa *tmpPessoa = (Pessoa *) calloc(1, sizeof(Pessoa));
    return tmpPessoa;
}

// Libera a memoria de um unica Pessoa
void killPessoa(Pessoa *tmpPessoa) {
    if (tmpPessoa != NULL) {
        free(tmpPessoa);
    }
}

// Deleta a Pessoa
void deletePessoa(Pessoa *tmpPessoa) {
    sprintf(tmpPessoa->cpf, "%s", "deletado");
}

// Retorna o tamanho de uma Pessoa
size_t getPessoaSize() {
    return sizeof(Pessoa);
}

// Set cpf
void setPessoaCpf(Pessoa *tmpPessoa, char tmpCpf[25]) {
    sprintf(tmpPessoa->cpf, "%s", tmpCpf);
}

// Set nome
void setPessoaNome(Pessoa *tmpPessoa, char tmpNome[50]) {
    sprintf(tmpPessoa->nome, "%s", tmpNome);
}

// Set sobrenome
void setPessoaSobrenome(Pessoa *tmpPessoa, char tmpSobre[50]) {
    sprintf(tmpPessoa->sobrenome, "%s", tmpSobre);
}

// Set sexo
void setPessoaSexo(Pessoa *tmpPessoa, char tmpSexo[2]) {
    sprintf(tmpPessoa->sexo, "%s", tmpSexo);
}

// Set nascimento
void setPessoaNasce(Pessoa *tmpPessoa, char tmpNasce[25]) {
    sprintf(tmpPessoa->nasce, "%s", tmpNasce);
}

// Get cpf
char *getPessoaCpf(Pessoa *tmpPessoa) {
    return tmpPessoa->cpf;
}

// Get nome
char *getPessoaNome(Pessoa *tmpPessoa) {
    return tmpPessoa->nome;
}

// Get sobrenome
char *getPessoaSobrenome(Pessoa *tmpPessoa) {
    return tmpPessoa->sobrenome;
}

// Get sexo
char *getPessoaSexo(Pessoa *tmpPessoa) {
    return tmpPessoa->sexo;
}

// Get nascimento
char *getPessoaNasce(Pessoa *tmpPessoa) {
    return tmpPessoa->nasce;
}

// Imprime as informações do Retangulo
void printPessoa(Pessoa *tmpPessoa) {
    printf("\ncpf = |%s|", tmpPessoa->cpf);
    printf("  nome = |%s|", tmpPessoa->nome);
    printf("  sobrenome = |%s|", tmpPessoa->sobrenome);
    printf("  sexo = |%s|", tmpPessoa->sexo);
    printf("  data = |%s|", tmpPessoa->nasce);
}
