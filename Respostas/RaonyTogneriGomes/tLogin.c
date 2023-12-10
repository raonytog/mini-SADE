#include "tLogin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tLogin {
    char user[20];
    char password[20];
};

tLogin * CriaLogin () {
    tLogin * login = calloc(1, sizeof(tLogin));
    if (!login) return NULL;

    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", login->user);

    printf("SENHA: ");
    scanf("%[^\n]%*c", login->password);

    return login;
}

tLogin * CriaLoginNULL () {
     tLogin * login = calloc(1, sizeof(tLogin));
    if (!login) return NULL;

    login->user[0] = '\0';
    login->password[0] = '\0';
    return login;
}

void DesalocaLogin (tLogin * login) {
    if (!login) return;
    free(login);
    login = NULL;
}

CARGO_LOGADO VerificaAutenticacao (tMedico ** medicos, int qtdMedicos, 
                           tSecretario ** secretarios, int qtdSecretarios,
                           char * user, char * password) {
    for (int i = 0; i < qtdSecretarios; i++) {
        if (VerificaUsuarioESenha(ObtemSecretarioLogin(secretarios[i]), user, password)) {
            if (SecretarioEhAdmin(secretarios[i])) return ADMIN;
            if (SecretarioEhUser(secretarios[i])) return USER;
        }
    }

    for (int i = 0; i < qtdMedicos; i++) {
        if (VerificaUsuarioESenha(ObtemMedicoLogin(medicos[i]), user, password)) {
            return MEDICO;
        }
    }

    return FALHA;
}

int EncontraIndiceMedicoLogado (tMedico ** medicos, int qtdMedicos, char * user, char * password) {
    for (int i = 0; i < qtdMedicos; i++) {
        if (VerificaUsuarioESenha( ObtemMedicoLogin(medicos[i]), user, password) ) {
            return i;
        }
    }
    return 0;
}

int EncontraIndiceSecretarioLogado (tSecretario ** secretarios, int qtdSecretarios, char * user, char * password) {
    for (int i = 0; i < qtdSecretarios; i++) {
        if (VerificaUsuarioESenha( ObtemSecretarioLogin(secretarios[i]), user, password) ) {
            return i;
        }
    }
    return 0;
}

bool VerificaUser (tLogin * login, char * usuario) {
    if (strcmp(login->user, usuario) == 0) return true;
    else return false;
}

bool VerificaSenha (tLogin * login, char * senha) {
    if (strcmp(login->password, senha) == 0) return true;
    else return false;
}

bool VerificaUsuarioESenha (tLogin * login, char * usuario, char * senha) {
    if (VerificaUser(login, usuario) && VerificaSenha(login, senha)) return true;
    else return false;
}

void SalvaLogin (tLogin * login, FILE * arquivo) {
    fwrite(login, sizeof(tLogin), 1, arquivo);
}

tLogin * RecuperaLogin (FILE * arquivo) {
    tLogin * login = (tLogin *) malloc (sizeof(tLogin));
    if (!login) {
        printf("Falha ao alocar memoria para recuperar login\n");
        exit(EXIT_FAILURE);
    }
    fread(login, sizeof(tLogin), 1, arquivo);
    return login;
}