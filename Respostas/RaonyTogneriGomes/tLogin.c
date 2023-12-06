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

bool VerificaUser (tLogin * login, char * usuario) {
    if (strcmp(login->user, usuario) == 0) return true;
    else return false;
}

bool VerificaSenha (tLogin * login, char * senha) {
    if (strcmp(login->password, senha) == 0) return true;
    else return false;
}

bool VerificaLogin (tLogin * login, char * usuario, char * senha) {
    if (VerificaUser(login, usuario) && VerificaSenha(login, senha)) return true;
    else return false;
}