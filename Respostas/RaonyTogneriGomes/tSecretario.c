#include "tSecretario.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tSecretario {
    tLogin * login;
};

tSecretario * CriaSecretario () {
    tSecretario * secretario = sizeof(tSecretario);
    if (!secretario) return NULL;

    char user[20], senha[20];
    scanf("%[\n]\n", user);
    scanf("%[\n]\n", senha);

    secretario->login = CriaLogin(user, senha);
    return secretario;
}

void DesalocaSecretario(tSecretario * secretario);

const char * ObtemCRM (tSecretario * secretario);

tLogin * ObtemLogin(tSecretario * secretario);
