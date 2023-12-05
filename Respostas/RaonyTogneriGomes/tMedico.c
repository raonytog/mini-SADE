#include "tMedico.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tMedico {
    char CRM[12];
    tLogin * login;
};

tMedico * CriaMedico () {
    tMedico * medico = malloc(sizeof(tMedico));
    scanf("%[^\n]\n", medico->CRM);

    char user[20], senha[20];
    scanf("%[\n]\n", user);
    scanf("%[\n]\n", senha);

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
    if (!medico) return '\0';
    return medico->CRM;
}

tLogin * ObtemLoginMedico (tMedico * medico) {
    if (!medico) return NULL;
    return medico->login;
}