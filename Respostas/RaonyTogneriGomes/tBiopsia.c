#include "tBiopsia.h"
#include <string.h>
#include <stdlib.h>

struct tBiopsia {
    tPessoa * paciente;
    tMedico * medico;
    tLesao ** lesoes;
    int qtdLesoes;
    char * data;
};

tBiopsia * CriaBiopsia (tPessoa * paciente, tLesao ** lesoes, int qtdLesoes, tMedico * medico, char *data) {
    tBiopsia * b = malloc(sizeof(tBiopsia));
    b->paciente = paciente;
    b->qtdLesoes = qtdLesoes;

    b->lesoes = malloc(qtdLesoes * sizeof(tLesao *));
    for (int i = 0; i < qtdLesoes; i++) {
        b->lesoes[i] = malloc(sizeof(tLesao *));
        b->lesoes = lesoes[i];
    }

    b->medico = medico;
    strcpy(b->data, data);
    return b;
}

void DesalocaBiopsia (tBiopsia * biopsia) {
    if (!biopsia) return;

    DesalocaPessoa(biopsia->paciente);
    DesalocaMedico(biopsia->medico);

    for (int i = 0; i < biopsia->qtdLesoes; i++) 
        DesalocaLesao(biopsia->lesoes[i]);
    
    free(biopsia->lesoes);
    free(biopsia);
}

void ImprimeBiopsiaTela (tBiopsia * biopsia) {
    printf("PACIENTE: %s\n", ObtemNomePessoa(biopsia->paciente));
    printf("CPF: %s\n\n", ObtemCPFPessoa(biopsia->paciente));

    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for (int i = 0; i < biopsia->qtdLesoes; i++) {
        ImprimeLesaoTela(biopsia->lesoes[i]);
    }

    printf("\n%s (%s)\n", ObtemNomeMedico(biopsia->medico), ObtemCRM(biopsia->medico));
    printf("%s\n\n", biopsia->data);
}

void ImprimeBiopsiaArquivo (tBiopsia * biopsia, FILE * arquivo) {
    sprintf(arquivo, "PACIENTE: %s\n", ObtemNomePessoa(biopsia->paciente));
    sprintf(arquivo, "CPF: %s\n\n", ObtemCPFPessoa(biopsia->paciente));

    sprintf(arquivo, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for (int i = 0; i < biopsia->qtdLesoes; i++) {
        ImprimeLesaoArquivo(biopsia->lesoes[i], arquivo);
    }

    sprintf(arquivo, "\n%s (%s)\n", ObtemNomeMedico(biopsia->medico), ObtemCRM(biopsia->medico));
    sprintf(arquivo, "%s\n\n", biopsia->data);
}

int ObtemQtdLesoes (tBiopsia * biopsia) {
    if (!biopsia) return 0;
    return biopsia->qtdLesoes;
}

tLesao * ObtemLesaoDoIndice (tBiopsia * biopsia, int indice) {
    if (!biopsia) return NULL;
    return biopsia->lesoes[indice];
}

tMedico * ObtemMedico (tBiopsia * biopsia) {
    if (!biopsia) return NULL;
}

tPessoa * ObtemPaciente (tBiopsia * biopsia) {
    if (!biopsia) return NULL;
}