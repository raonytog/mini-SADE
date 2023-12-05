#include "tBiopsia.h"
#include <string.h>
#include <stdlib.h>

struct tBiopsia {
    tLesao ** lesoes;
    char nomePaciente[100];
    char cpf[15];
    char nomeMedico[20];
    char CRM[12];
    char data[10];
    int qtdLesoes;
};

tBiopsia * CriaBiopsia (char * nomePaciente, char * CPF, tLesao ** lesoes, int qtdLesoes, char *nomeMedico, char *CRM, char *data) {
    tBiopsia * b = malloc(sizeof(tBiopsia));
    if (!b) return NULL;

    strcpy(b->nomePaciente, nomePaciente);
    strcpy(b->cpf, CPF);
    b->qtdLesoes = qtdLesoes;

    b->lesoes = malloc(qtdLesoes * sizeof(tLesao *));
    for (int i = 0; i < qtdLesoes; i++) {
        b->lesoes[i] = lesoes[i];
    }

    strcpy(b->nomeMedico, nomeMedico);
    strcpy(b->CRM, CRM);
    strcpy(b->data, data);

    return b;
}

void DesalocaBiopsia (tBiopsia * biopsia) {
    if (!biopsia) return;

    for (int i = 0; i < biopsia->qtdLesoes; i++) 
        DesalocaLesao(biopsia->lesoes[i]);
    
    free(biopsia->lesoes);
    free(biopsia);
}

void ImprimeBiopsiaTela (void * data) {
    tBiopsia * biopsia = (tBiopsia *) data;

    printf("PACIENTE: %s\n", biopsia->nomePaciente);
    printf("CPF: %s\n\n", biopsia->cpf);

    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for (int i = 0; i < biopsia->qtdLesoes; i++)
        ImprimeLesaoTela(biopsia->lesoes[i]);

    printf("\n%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);
    printf("%s\n\n", biopsia->data);
}

void ImprimeBiopsiaArquivo (void * data, FILE * arquivo) {
    tBiopsia * biopsia = (tBiopsia *) data;

    fprintf(arquivo, "PACIENTE: %s\n", biopsia->nomePaciente);
    fprintf(arquivo, "CPF: %s\n\n", biopsia->cpf);

    fprintf(arquivo, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for (int i = 0; i < biopsia->qtdLesoes; i++) {
        ImprimeLesaoArquivo(biopsia->lesoes[i], arquivo);
    }

    fprintf(arquivo, "\n%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);
    fprintf(arquivo, "%s\n\n", biopsia->data);
}

int ObtemQtdLesoes (tBiopsia * biopsia) {
    if (!biopsia) return 0;
    return biopsia->qtdLesoes;
}

tLesao * ObtemLesaoDoIndice (tBiopsia * biopsia, int indice) {
    if (!biopsia) return NULL;
    return biopsia->lesoes[indice];
}
