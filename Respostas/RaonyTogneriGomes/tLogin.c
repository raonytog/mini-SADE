#include "tLogin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tLogin {
    char user[20];
    char password[20];
};

tLogin * CriaLogin (char * user, char * password) {
    tLogin * login = malloc(sizeof(tLogin));
    if (!login) return NULL;

    strcpy(login->user, user);
    strcpy(login->password, password);

    return login;
}

void DesalocaLogin (tLogin * login) {
    free(login);
}

void AlteraLogin (tLogin * login) {
    // nem vou fazer agora
}

bool VerificaUser (tLogin * login, char * usuario) {
    return strcmp(login->user, usuario);
}

bool VerificaSenha (tLogin * login, char * senha) {
    return strcmp(login->password, senha);
}