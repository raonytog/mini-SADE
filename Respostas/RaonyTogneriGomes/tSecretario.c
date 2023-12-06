#include "tSecretario.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tSecretario {
    tPessoa * pessoa;
    tLogin * login;
    char nivelAcesso[5];
};

tSecretario * CriaSecretario () {
    char user[20] = '\0', senha[20] = '\0';
    tSecretario * secretario = malloc(sizeof(tSecretario));
    if (!secretario) return NULL;

    tPessoa * pessoa = CriaPessoa();
    secretario->pessoa = pessoa;
    
    printf("NOME DE USUARIO: ");
    scanf("%[\n]%*c", user);

    printf("SENHA: ");
    scanf("%[\n]%*c", senha);
    secretario->login = CriaLogin(user, senha);

    printf("NIVEL DE ACESSO: ");
    scanf("%[\n]%*c", secretario->nivelAcesso);
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
    
    if (secretario->nivelAcesso == "USER") return true;
    return false;
}

bool SecretarioEhAdmin (tSecretario * secretario) {
    if (!secretario) return false;

    if (secretario->nivelAcesso == "ADMIN") return true;
    return false;
}