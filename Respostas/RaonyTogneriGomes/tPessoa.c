#include "tPessoa.h"
#include "tSecretario.h"
#include "tMedico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tPessoa {
    char nome[100];
    char cpf[15];
    tData * data;
    char telefone[14];
    char genero[9];
};

tPessoa * CriaPessoa() {
    tPessoa * pessoa = malloc(sizeof(tPessoa));
    if (!pessoa) return NULL;

    printf("NOME COMPLETO: ");          scanf("%[^\n]%*c", pessoa->nome);
    printf("CPF: ");                    scanf("%[^\n]%*c", pessoa->cpf);
    pessoa->data = LeData();
    printf("TELEFONE: ");               scanf("%[^\n]%*c", pessoa->telefone);
    printf("GENERO: ");                 scanf("%[^\n]%*c", pessoa->genero);
    return pessoa;
}

void DesalocaPessoa(void * dado) {
    tPessoa * pessoa = (tPessoa *) dado;
    if (!pessoa) return;
    free(pessoa);
}

tData * ObtemDataPessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    return pessoa->data;
}

char * ObtemNomePessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * nome = pessoa->nome;
    return nome;
}

char * ObtemCPFPessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    char * cpf = pessoa->cpf;
    return cpf;
}

char * ObtemTelefonePessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * telefone = pessoa->telefone;
    return telefone;
}

char * ObtemGeneroPessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * genero = pessoa->genero;
    return genero;
}