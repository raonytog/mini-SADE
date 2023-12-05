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
    CARGO cargo;
    void * cargoOcupado;
};

tPessoa * CriaPessoa(int cargo) {
    tPessoa * pessoa = malloc(sizeof(tPessoa));
    if (!pessoa) return NULL;

    scanf("%[^\n]\n", pessoa->nome);
    scanf("%[^\n]\n", pessoa->cpf);
    scanf("%[^\n]\n", pessoa->dataNascimento);
    scanf("%[^\n]\n", pessoa->telefone);
    scanf("%[^\n]\n", pessoa->genero);
    pessoa->cargo = PACIENTE;
    pessoa->cargoOcupado = NULL;

    // a verificar se cadastrado !!!
    switch (cargo) {
        case SECRETARIO:
            pessoa->cargo = SECRETARIO;
            pessoa->cargoOcupado = CriaSecretario();
            break;

        case MEDICO:
            pessoa->cargo = MEDICO;
            pessoa->cargoOcupado = CriaMedico();
            break;
    }

    return pessoa;
}

void DesalocaPessoa(void * dado) {
    tPessoa * pessoa = (tPessoa *) dado;
    if (!pessoa) return;

    switch (pessoa->cargo) {
        case SECRETARIO:
            DesalocaSecretario(pessoa->cargoOcupado);
            break;

        case MEDICO:
            DesalocaMedico(pessoa->cargoOcupado);
            break;
    }

    free(pessoa);
}

const char * ObtemNomePessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    return pessoa->nome;
}

const char * ObtemNomeMedico (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    if (ObtemCargoPessoa(pessoa) == MEDICO) return pessoa->nome;
    return '\0';
}

const char * ObtemNomeSecretario (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    if (ObtemCargoPessoa(pessoa) == SECRETARIO) return pessoa->nome;
    return '\0';
}

const char * ObtemCPFPessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    return pessoa->cpf;
}

const char * ObtemDataNascimentoPessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    return pessoa->dataNascimento;
}

const char * ObtemTelefonePessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    return pessoa->telefone;
}

const char * ObtemGeneroPessoa (tPessoa * pessoa) {
    if (!pessoa) return '\0';
    return pessoa->genero;
}

CARGO ObtemCargoPessoa (tPessoa * pessoa) {
    if (!pessoa) return NAO_EXISTE;
    return pessoa->cargo;
}