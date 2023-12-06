#include "tPessoa.h"
#include "tSecretario.h"
#include "tMedico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tPessoa {
    char nome[100];
    char cpf[15];
    char dataNascimento[10];
    char telefone[14];
    char genero[9];
};

tPessoa * CriaPessoa() {
    tPessoa * pessoa = malloc(sizeof(tPessoa));
    if (!pessoa) return NULL;

    printf("NOME COMPLETO: ");           scanf("%[^\n]%*c", pessoa->nome);
    printf("CPF: ");                    scanf("%[^\n]%*c", pessoa->cpf);
    printf("DATA DE NASCIMENTO: ");     scanf("%[^\n]%*c", pessoa->dataNascimento);
    printf("TELEFONE: ");               scanf("%[^\n]%*c", pessoa->telefone);
    printf("GENERO: ");                 scanf("%[^\n]%*c", pessoa->genero);
    return pessoa;
}

void DesalocaPessoa(void * dado) {
    tPessoa * pessoa = (tPessoa *) dado;
    if (!pessoa) return;
    free(pessoa);
}

const char * ObtemNomePessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * nome = pessoa->nome;
    return nome;
}

const char * ObtemCPFPessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    char * cpf = pessoa->cpf;
    return cpf;
}

const char * ObtemDataNascimentoPessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    char * data = pessoa->dataNascimento;
    return data;
}

const char * ObtemTelefonePessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * telefone = pessoa->telefone;
    return telefone;
}

const char * ObtemGeneroPessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * genero = pessoa->genero;
    return genero;
}