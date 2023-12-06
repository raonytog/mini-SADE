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
    tMedico * medico = malloc(sizeof(tMedico));
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
    free(medico);
}

const char * ObtemNomeMedico (tMedico * medico) {
    if (!medico) return NULL;
    char * nomemed = ObtemNomePessoa(medico->pessoa);
    return nomemed;
}

const char * ObtemCRM (tMedico * medico) {
    if (!medico) return '\0';
    char * crm = medico->CRM;
    return crm;
}

tLogin * ObtemLoginMedico (tMedico * medico) {
    if (!medico) return NULL;
    return medico->login;
}