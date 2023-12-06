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
    char user[20], senha[20];
    tMedico * medico = malloc(sizeof(tMedico));
    if (!medico) return NULL;

    tPessoa * pessoa = CriaPessoa();
    medico->pessoa = pessoa;

    printf("CRM: ");
    scanf("%[^\n]%*c", medico->CRM);

    printf("NOME DE USUARIO: ");
    scanf("%[\n]%*c", user);

    printf("SENHA: ");
    scanf("%[\n]%*c", senha);
    tLogin * login = CriaLogin(user, senha);
    medico->login = login;

    return medico;
}

void DesalocaMedico(tMedico * medico) {
    if (!medico) return;
    DesalocaLogin(medico->login);
    free(medico);
}

const char * ObtemCRM (tMedico * medico) {
    if (!medico) return NULL;
    return medico->CRM;
}

tLogin * ObtemLoginMedico (tMedico * medico) {
    if (!medico) return NULL;
    return medico->login;
}