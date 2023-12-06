#include "tListaPessoas.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct tListaPessoas {
    tPessoa ** pessoas;
    int qtdPessoas;
};

tListaPessoas * CriaListaBusca() {
    tListaPessoas * lista = malloc(sizeof(tListaPessoas));
    if (!lista) return NULL;

    lista->qtdPessoas = 0;
    lista->pessoas = NULL;

    return lista;
}

int ObtemNumeroPessoasLista (tListaPessoas * lista) {
    if (!lista) return 0;
    return lista->qtdPessoas;
}

void AdiconaPessoaLista (tListaPessoas * lista, tPessoa * pessoa, char * nome) {
    if (!lista) return;

    if (strcmp(ObtemNomePessoa(pessoa), nome) != 0) return; 

    (lista->qtdPessoas)++;
    lista->pessoas = realloc(lista->pessoas, lista->qtdPessoas * sizeof(tPessoa *));
    lista->pessoas[lista->qtdPessoas-1] = pessoa;
}

void DesalocaLista (tListaPessoas * lista) {
    if (!lista) return;

    for (int i = 0; i < lista->qtdPessoas; i++)
        DesalocaPessoa(lista->pessoas[i]);

    free(lista->pessoas);
    free(lista);
}

void ImprimeNomeRequisitadoTela (tListaPessoas * lista, char * nome) {
    if (!lista) return;

    for (int i = 0; i < lista->qtdPessoas; i++) {
        if (strcmp(ObtemNomePessoa(lista->pessoas[i]), nome) == 0)
            printf("%d - %s (%s)\n", i+1, 
                    ObtemNomePessoa(lista->pessoas[i]), ObtemCPFPessoa(lista->pessoas[i]));
    }
}

void ImprimeNomeRequisitadoArquivo (tListaPessoas * lista, char * nome, char * path) {
    if (!lista) return;

    int req = 0;
    char diretorio[1001];
    sprintf(diretorio, "%s/lista_busca.txt", path);
    FILE * fListaBusca = NULL;
    fListaBusca = fopen(diretorio, "a+b");

    for (int i = 0; i < lista->qtdPessoas; i++) {
        if (strcmp(ObtemNomePessoa(lista->pessoas[i]), nome) == 0) {
            req++;
            fprintf(fListaBusca, "%d - %s (%s)\n", req, ObtemNomePessoa(lista->pessoas[i]), ObtemCPFPessoa(lista->pessoas[i]));
        }
    }

    fclose(fListaBusca);
}