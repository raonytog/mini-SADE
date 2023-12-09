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

void DesalocaMedico(tMedico * medico) {
    if (!medico) return;
    DesalocaLogin(medico->login);
    DesalocaPessoa(medico->pessoa);
    free(medico);
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