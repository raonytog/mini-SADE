#include "tListaPessoas.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct tListaPessoas {
    tPessoa ** pessoas;
    int qtdPessoas;
};

tListaPessoas * CriaListaBusca() {
    tListaPessoa * lista = malloc(sizeof(tListaPessoas));
    if (!lista) return NULL;

    lista->qtdPessoas = 0;
    lista->pessoas = NULL;

    return lista;
}

void AdiconaPessoaLista (tListaPessoas ** lista, tPessoa * pessoa) {
    if (!lista) return;
    (lista->qtdPessoas)++;
    lista->pessoas = realloc(lista->pessoas, lista->qtdPessoas * sizeof(tPessoa *));
    lista->pessoas[lista->qtdPessoas-1] = pessoa;
}

void DesalocaLista (tListaPessoas ** lista) {
    if (!lista) return;

    for (int i = 0; i < lista->qtdPessoas; i++)
        DesalocaPessoa(lista->pessoas[i]);

    free(lista->pessoas);
    free(lista);
}