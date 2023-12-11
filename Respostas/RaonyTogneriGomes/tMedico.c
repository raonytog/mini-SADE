#include "tMedico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tMedico {
    tPessoa * pessoa;
    char CRM[12];
    tLogin * login;
};

tMedico * CriaMedico () {
    tMedico * medico = calloc(1, sizeof(tMedico));
    if (!medico) return NULL;

    tPessoa * pessoa = CriaPessoa();
    medico->pessoa = pessoa;

    printf("CRM: ");
    scanf("%[^\n]%*c", medico->CRM);

    tLogin * login = CriaLogin();
    medico->login = login;
    return medico;
}

tMedico * CriaMedicoNULL () {
    tMedico * medico = calloc(1, sizeof(tMedico));
    if (!medico) return NULL;

    medico->pessoa = CriaPessoaNULL();
    medico->CRM[0] = '\0';
    medico->login = CriaLoginNULL();
    return medico;
}

void DesalocaMedico(tMedico * medico) {
    if (!medico) return;
    DesalocaLogin(medico->login);
    medico->login = NULL;
    DesalocaPessoa(medico->pessoa);
    medico->pessoa = NULL;
    free(medico);
    medico = NULL;
}

bool ExisteMedicoCpf(tMedico ** medicos, int qtdMedicos, tMedico * medicoEmAnalise) {
    int contagem = 0;
    for (int i = 0; i < qtdMedicos; i++) 
        if (strcmp(ObtemCPFPessoa(medicos[i]->pessoa), ObtemCPFPessoa(medicoEmAnalise->pessoa)) == 0) {
            contagem++;
            if (contagem >= 2) return true;
        }
    return false;
}

char * ObtemNomeMedico (tMedico * medico) {
    if (!medico) return '\0';
    char * nomemed = ObtemNomePessoa(medico->pessoa);
    return nomemed;
}

char * ObtemCRM (tMedico * medico) {
    if (!medico) return '\0';
    char * crm = medico->CRM;
    return crm;
}

char * ObtemMedicoCPF (tMedico * medico) {
    if (!medico) return '\0';
    char * cpf = ObtemCPFPessoa(medico->pessoa);
    return cpf;
}

tLogin * ObtemMedicoLogin (tMedico * medico) {
    if (!medico) return NULL;
    return medico->login;
}

void SalvaMedico (tMedico * medico, FILE * arquivo) {
    fwrite(medico, sizeof(tMedico), 1, arquivo);
    SalvaPessoa(medico->pessoa, arquivo);
    SalvaLogin(medico->login, arquivo);
}

tMedico ** RecuperaMedicos (FILE * arquivo, int * qtdMedicos){
    fread(qtdMedicos, sizeof(int), 1, arquivo);
    tMedico ** medico = (tMedico **) malloc (*qtdMedicos * sizeof(tMedico *));
    if (!medico) {
        printf("Falha ao alocar memoria para recuperar medico\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *qtdMedicos; i++) {
        medico[i] = malloc(sizeof(tMedico));
        fread(medico[i], sizeof(tMedico), 1, arquivo);

        medico[i]->pessoa = RecuperaUmaPessoa(arquivo);
        medico[i]->login = RecuperaLogin(arquivo);
    }

    return medico;
}

tMedico * RecuperaUmMedico (FILE * arquivo) {
    tMedico * medico = (tMedico *) calloc (1, sizeof(tMedico));
    fread(medico, sizeof(tMedico), 1, arquivo);
    medico->login = RecuperaLogin(arquivo);
    return medico;
}

void SalvaMedicoBinario (tMedico ** medicos, int qtdMedicos, char * path) {
    char dir[1001];
    sprintf(dir, "%s/medicos.bin", path);
    FILE * arquivo = fopen(dir, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&qtdMedicos, sizeof(int), 1, arquivo);
    for (int i = 0; i < qtdMedicos; i++) {
        fwrite(medicos[i], sizeof(tMedico), 1, arquivo);
        SalvaPessoa(medicos[i]->pessoa, arquivo);
        SalvaLogin(medicos[i]->login, arquivo);
    }

    fclose(arquivo);
}