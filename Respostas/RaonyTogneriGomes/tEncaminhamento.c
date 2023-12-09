#include "tEncaminhamento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tEncaminhamento {
    char nomePaciente[100];
    char CPF[15];
    char especialidade[50];
    char motivo[300];
    char nomeMedico[20];
    char CRM[12];
    char data[11];
};

tEncaminhamento * CriaEncaminhamento (char * nomePaciente, char * CPF, char * especialidade, char * motivo, char * nomeMedico, char *CRM, char *data) {
    tEncaminhamento * e = calloc(1, sizeof(tEncaminhamento));
    if (!e) return NULL;

    strcpy(e->nomePaciente, nomePaciente);
    strcpy(e->CPF, CPF);
    strcpy(e->especialidade, especialidade);
    strcpy(e->motivo, motivo);
    if (nomeMedico != NULL) strcpy(e->nomeMedico, nomeMedico);
    else e->nomeMedico[0] = '\0';

    if (CRM != NULL) strcpy(e->CRM, CRM);
    else e->CRM[0] = '\0';
    strcpy(e->data, data);

    return e;
}

void DesalocaEncaminhamento (void * data) {
    tEncaminhamento * encaminhamento = (tEncaminhamento *) data;
    // if (!encaminhamento) return;
    free(encaminhamento);
}

void ImprimeEncaminhamentoTela (void * data) {
    tEncaminhamento * e = (tEncaminhamento *) data;
    printf("PACIENTE: %s\n", e->nomePaciente);
    printf("CPF: %s\n\n", e->CPF);

    printf("ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    printf("MOTIVO: %s\n\n", e->motivo);

    printf("%s (%s)\n", e->nomeMedico, e->CRM);
    printf("%s\n\n", e->data);
}

void ImprimeEncaminhamentoArquivo (void * data, char * path) {
    tEncaminhamento * e = (tEncaminhamento *) data;

    char diretorio[1001];
    sprintf(diretorio, "%s/encaminhamento.txt", path);
    FILE * fEncaminhamento = NULL;
    fEncaminhamento = fopen(diretorio, "a");

    fprintf(fEncaminhamento, "PACIENTE: %s\n", e->nomePaciente);
    fprintf(fEncaminhamento, "CPF: %s\n\n", e->CPF);

    fprintf(fEncaminhamento, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    fprintf(fEncaminhamento, "MOTIVO: %s\n\n", e->motivo);

    fprintf(fEncaminhamento, "%s (%s)\n", e->nomeMedico, e->CRM);
    fprintf(fEncaminhamento, "%s\n\n", e->data);
    
    fclose(fEncaminhamento);
}



