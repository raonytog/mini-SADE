#include "tReceita.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct tReceita {
    eTipoUso tipoUso;
    int qtd;
    char nomePaciente[100];
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char instrucoes[MAX_TAM_INSTRUCOES];
    char nomeMedico[50];
    char CRM[13];
    char dataString[15];
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr) {

    tReceita * receita = calloc (1, sizeof(tReceita));
    if (receita == NULL) return NULL;

    receita->tipoUso = tipoUso;
    receita->qtd = qntd;

    strcpy(receita->nomePaciente, nomePaciente);
    strcpy(receita->nomeMedicamento, nomeMedicamento);
    strcpy(receita->tipoMedicamento, tipoMedicamento);
    strcpy(receita->instrucoes, instrucoes);

    if (nomeMedico != NULL) strcpy(receita->nomeMedico, nomeMedico);
    else receita->nomeMedico[0] = '\0';

    if (CRM != NULL) strcpy(receita->CRM, CRM);
    else receita->CRM[0] = '\0';

    strcpy(receita->dataString, dataStr);

    return receita;
}


void desalocaReceita(void *dado) {
    if (!dado) return;

    tReceita * receita = (tReceita*) dado;
    free(receita);
    receita = NULL;
}

void imprimeNaTelaReceita(void *dado) {
    tReceita * r = (tReceita*) dado;

    printf("RECEITUARIO\n");
    printf("NOME: %s\n\n", r->nomePaciente);

    switch (r->tipoUso) {
        case ORAL:
            printf("USO ORAL\n\n");
            break;

        case TOPICO:
            printf("USO TOPICO\n\n");
            break;
    }

    printf("%s\n", r->nomeMedicamento);
    printf("%d %s\n\n", r->qtd, r->tipoMedicamento);
    printf("%s\n\n", r->instrucoes);
    

    printf("%s (%s)\n", r->nomeMedico, r->CRM);
    printf("%s\n\n", r->dataString);
}

void imprimeEmArquivoReceita(void *dado, char *path) {
    char diretorio[1001];
    sprintf(diretorio, "%s/receita.txt", path);

    tReceita * r = (tReceita *) dado;
    FILE * fReceita = NULL;
    fReceita = fopen(diretorio, "a+b");
    if (!fReceita) {
        printf("fReceita nao abriu\n");
        return;
    }

    fprintf(fReceita, "RECEITUARIO\n");
    fprintf(fReceita, "NOME: %s\n\n", r->nomePaciente);

    switch (r->tipoUso) {
        case ORAL:
            fprintf(fReceita, "USO ORAL\n\n");
            break;

        case TOPICO:
            fprintf(fReceita, "USO TOPICO\n\n");
            break;
    }

    fprintf(fReceita, "%s\n", r->nomeMedicamento);
    fprintf(fReceita, "%d %s\n\n", r->qtd, r->tipoMedicamento);
    fprintf(fReceita, "%s\n\n", r->instrucoes);
    
    fprintf(fReceita, "%s (%s)\n", r->nomeMedico, r->CRM);

    fprintf(fReceita, "%s\n\n", r->dataString);

    fclose(fReceita);
}
