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
    tSecretario * secretario = calloc(1, sizeof(tSecretario));
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
    secretario->login = NULL;
    DesalocaPessoa(secretario->pessoa);
    secretario->pessoa = NULL;
    free(secretario);
    secretario = NULL;
}

bool ExisteSecretarioCpf(tSecretario ** secretarios, int qtdSecretarios, tSecretario * secretarioEmAnalise) {
    int contagem = 0;
    for (int i = 0; i < qtdSecretarios; i++) 
        if (strcmp(ObtemCPFPessoa(secretarios[i]->pessoa), ObtemCPFPessoa(secretarioEmAnalise->pessoa)) == 0) {
            contagem++;
            if (contagem >= 2) return true;
        }
    return false;
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

tLogin * ObtemSecretarioLogin (tSecretario * secretario) {
    if (!secretario) return NULL;
    return secretario->login;
}