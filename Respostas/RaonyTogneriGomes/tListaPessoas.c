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

tPessoa * ObtemPessoaIndice (tListaPessoas * lista, int indice) {
    if (!lista) return NULL;
    return lista->pessoas[indice];
}

int ObtemNumeroPessoasLista (tListaPessoas * lista) {
    if (!lista) return 0;
    return lista->qtdPessoas;
}

void AdiconaPessoaLista (tListaPessoas * lista, tPessoa * pessoa) {
    if (!lista) return;

    (lista->qtdPessoas)++;
    lista->pessoas = realloc(lista->pessoas, lista->qtdPessoas * sizeof(tPessoa *));
    lista->pessoas[lista->qtdPessoas-1] = pessoa;
}

void DesalocaLista (void * data) {
    tListaPessoas * lista = (tListaPessoas *) data;
    if (!lista) return;

    for (int i = 0; i < lista->qtdPessoas; i++)
        DesalocaPessoa(lista->pessoas[i]);

    free(lista->pessoas);
    free(lista);
}

void ImprimeNomeRequisitadoTela (void * data) {
    tListaPessoas * lista = (tListaPessoas *) data;
    if (!lista) return;

    printf("PACIENTES ENCONTRADOS:\n");
    for (int i = 0; i < lista->qtdPessoas; i++)
        printf("%d - %s (%s)\n", i+1, ObtemNomePessoa(lista->pessoas[i]), ObtemCPFPessoa(lista->pessoas[i]));
    printf("\n");
}

void ImprimeMenuBuscarPacientes (tFila * fila, tListaPessoas * lista) {
    int opcao = 0;
    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) ENVIAR LISTA PARA IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU PRINCIPAL\n");
    printf("############################################################\n");
    scanf("%d%*c", &opcao);

    if (opcao == 1) {
        insereDocumentoFila(fila, lista, ImprimeNomeRequisitadoTela, ImprimeNomeRequisitadoArquivo, DesalocaLista);
        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
        printf("############################################################\n");
    }
}

void ImprimeNomeRequisitadoArquivo (void * data, char * path) {
    tListaPessoas * lista = (tListaPessoas *) data;
    if (!lista) return;

    char diretorio[1001];
    sprintf(diretorio, "%s/lista_busca.txt", path);
    
    FILE * fListaBusca = NULL;
    fListaBusca = fopen(diretorio, "a+b");
    if (!fListaBusca) 
        printf("NAO ABRIU");

    char nome[100], cpf[15];

    for (int i = 0; i < lista->qtdPessoas; i++) {
        strcpy(nome, ObtemNomePessoa(lista->pessoas[i]));
        strcpy(cpf, ObtemCPFPessoa(lista->pessoas[i]));
        fprintf(fListaBusca, "%d - %s (%s)\n", i+1, nome, cpf);
    }

    fclose(fListaBusca);
}