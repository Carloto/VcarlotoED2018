// Define
#ifndef PESSOA_H
#define PESSOA_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscfunctions.h"
#include "filehandling.h"

typedef struct tmpPess Pessoa; // Guarda as infoemações de uma pessoa

// Aloca e inicializa uma struct Pessoa
Pessoa *allocPessoa();

// Libera a memoria de um unica Pessoa
void killPessoa(Pessoa *tmpPessoa);

// Deleta a Pessoa
void deletePessoa(Pessoa *tmpPessoa);

// Retorna o tamanho de uma Pessoa
size_t getPessoaSize();

// Set cpf
void setPessoaCpf(Pessoa *tmpPessoa, char tmpCpf[25]);

// Set nome
void setPessoaNome(Pessoa *tmpPessoa, char tmpNome[50]);

// Set sobrenome
void setPessoaSobrenome(Pessoa *tmpPessoa, char tmpSobre[50]);

// Set sexo
void setPessoaSexo(Pessoa *tmpPessoa, char tmpSexo[2]);

// Set nascimento
void setPessoaNasce(Pessoa *tmpPessoa, char tmpNasce[25]);

// Get cpf
char *getPessoaCpf(Pessoa *tmpPessoa);

// Get nome
char *getPessoaNome(Pessoa *tmpPessoa);

// Get sobrenome
char *getPessoaSobrenome(Pessoa *tmpPessoa);

// Get sexo
char *getPessoaSexo(Pessoa *tmpPessoa);

// Get nascimento
char *getPessoaNasce(Pessoa *tmpPessoa);

// Imprime as informações do Retangulo
void printPessoa(Pessoa *tmpPessoa);

#endif // PESSOA_H
