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
    tSecretario * secretario = malloc(sizeof(tSecretario));
    if (!secretario) return NULL;

    tPessoa * pessoa = CriaPessoa();
    secretario->pessoa = pessoa;
    
    secretario->login = CriaLogin();

    printf("NIVEL DE ACESSO: ");
    scanf("%[^\n]%*c", secretario->nivelAcesso);
    return secretario;
}

void DesalocaSecretario(tSecretario * secretario) {
    if (!secretario) return;
    DesalocaLogin(secretario->login);
    free(secretario);
}

char * ObtemSecretarioCPF (tSecretario * secretario) {
    if (!secretario) return '\0';
    char * cpf = ObtemCPFPessoa(secretario->pessoa);
    return cpf;
}

bool SecretarioEhUser (tSecretario * secretario) {
    if (!secretario) return false;
    
    if (strcmp(secretario->nivelAcesso, "USER") == 0) return true;
    return false;
}

bool SecretarioEhAdmin (tSecretario * secretario) {
    if (!secretario) return false;

    if (strcmp(secretario->nivelAcesso, "ADMIN") == 0) return true;
    return false;
}