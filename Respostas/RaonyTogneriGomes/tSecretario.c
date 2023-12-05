#include "tSecretario.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tSecretario {
    tLogin * login;
    PODER_USUARIO poder;
};

tSecretario * CriaSecretario () {
    tSecretario * secretario = malloc(sizeof(tSecretario));
    if (!secretario) return NULL;

    char user[20], senha[20];
    scanf("%[\n]\n", user);
    scanf("%[\n]\n", senha);

    secretario->login = CriaLogin(user, senha);
    return secretario;
}

void DesalocaSecretario(tSecretario * secretario) {
    if (!secretario) return;
    DesalocaLogin(secretario->login);
    free(secretario);
}

tLogin * ObtemLoginSecretario (tSecretario * secretario) {
    if (!secretario) return NULL;
    return secretario->login;
}

bool SecretarioEhUser (tSecretario * secretario) {
    if (!secretario) return false;
    
    if (secretario->poder == USER) return true;
    return false;
}

bool SecretarioEhAdmin (tSecretario * secretario) {
    if (!secretario) return false;

    if (secretario->poder == ADMIN) return true;
    return false;
}