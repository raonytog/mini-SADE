#include "tPessoa.h"
#include "tSecretario.h"
#include "tMedico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tPessoa {
    char nome[100];
    char cpf[15];
    int dia, mes, ano;
    char data[20];
    char telefone[14];
    char genero[10];
    int jaConsultado;
};

tPessoa * CriaPessoa () {
    tPessoa * pessoa = calloc(1, sizeof(tPessoa));
    if (!pessoa) return NULL;
    pessoa->jaConsultado = 0;
    printf("NOME COMPLETO: ");          scanf("%[^\n]%*c", pessoa->nome);
    printf("CPF: ");                    scanf("%[^\n]%*c", pessoa->cpf);
    printf("DATA DE NASCIMENTO: ");     scanf("%d/%d/%d%*c", &pessoa->dia, &pessoa->mes, &pessoa->ano);
    printf("TELEFONE: ");               scanf("%[^\n]%*c", pessoa->telefone);
    printf("GENERO: ");                 scanf("%[^\n]%*c", pessoa->genero);

    sprintf(pessoa->data, "%d/%d/%d", pessoa->dia, pessoa->mes, pessoa->ano);
    return pessoa;
}

tPessoa * CriaPessoaNULL () {
    tPessoa * pessoa = calloc(1, sizeof(tPessoa));
    if (!pessoa) return NULL;

    pessoa->cpf[0] = '\0';
    pessoa->data[0] = '\0';
    pessoa->genero[0] = '\0';
    pessoa->nome[0] = '\0';
    pessoa->telefone[0] = '\0';
    return pessoa;
}

void DesalocaPessoa(void * dado) {
    tPessoa * pessoa = (tPessoa *) dado;
    if (!pessoa) return;


    free(pessoa);
    pessoa = NULL;
}

bool ExistePessoaCpf(tPessoa ** pessoas, int qtdPessoas, tPessoa * pessoaEmAnalise) {
    int contagem = 0;
    for (int i = 0; i < qtdPessoas; i++) 
        if (strcmp(ObtemCPFPessoa(pessoas[i]), ObtemCPFPessoa(pessoaEmAnalise)) == 0) {
            contagem++;
            if (contagem >= 2) return true;
        }
    return false;
}

char * ObtemDataPessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * data = pessoa->data;
    return data;
}

char * ObtemNomePessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
    char * nome = pessoa->nome;
    return nome;
}

char * ObtemCPFPessoa (tPessoa * pessoa) {
    if (!pessoa) return NULL;
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

int ObtemSeFoiAtendido (tPessoa * pessoa) {
    return pessoa->jaConsultado;
}

int ObtemDiaPessoa (tPessoa * pessoa) {
    if (!pessoa) return 0;
    return pessoa->dia;
}

int ObtemMesPessoa (tPessoa * pessoa) {
    if (!pessoa) return 0;
    return pessoa->mes;
}

int ObtemAnoPessoa (tPessoa * pessoa) {
    if (!pessoa) return 0;
    return pessoa->ano;
}

void AtualizaPessoaComoAtendida (tPessoa * pessoa) {
    pessoa->jaConsultado = 1;
}

void SalvaPessoa (tPessoa * pessoa, FILE * arquivo) {
    fwrite(pessoa, sizeof(tPessoa), 1, arquivo);
}

tPessoa ** RecuperaPessoas (FILE * arquivo, int * qtdPessoas) {
    fread(qtdPessoas, sizeof(int), 1, arquivo);
    tPessoa ** pessoa = (tPessoa **) calloc(*qtdPessoas, sizeof(tPessoa *));
    if (!pessoa) {
        printf("Erro ao alocar memória para recuperar pessoa\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *qtdPessoas; i++) {
        pessoa[i] = malloc(sizeof(tPessoa));
        fread(pessoa[i], sizeof(tPessoa), 1, arquivo);
    }
    
    return pessoa;
}

tPessoa * RecuperaUmaPessoa (FILE * arquivo) {
    tPessoa * pessoa = (tPessoa *) calloc (1, sizeof(tPessoa));
    fread(pessoa, sizeof(tPessoa), 1, arquivo);
    return pessoa;
}

void SalvaPessoaBinario (tPessoa ** pessoas, int qtdPessoas, char * path) {
    char dir[1500];
    sprintf(dir, "%s/pessoas.bin", path);
    FILE * arquivo = fopen(dir, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar pessoa no binario\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&qtdPessoas, sizeof(int), 1, arquivo);
    for (int i = 0; i < qtdPessoas; i++) {
        fwrite(pessoas[i], sizeof(tPessoa), 1, arquivo);
    }

    fclose(arquivo);
}