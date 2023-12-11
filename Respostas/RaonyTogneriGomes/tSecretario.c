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

void SalvaSecretario (tSecretario * secretario, FILE * arquivo) {
    fwrite(secretario, sizeof(tSecretario), 1, arquivo);
    SalvaPessoa(secretario->pessoa, arquivo);
    SalvaLogin(secretario->login, arquivo);
}

tSecretario ** RecuperaSecretario (FILE * arquivo, int * qtdSecretarios) {
    fread(qtdSecretarios, sizeof(int), 1, arquivo);
    tSecretario ** secretario = (tSecretario **) calloc(*qtdSecretarios, sizeof(tSecretario *));
    if (!secretario) {
        printf("Erro ao alocar memória para recuperar secretario\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *qtdSecretarios; i++) {
        secretario[i] = realloc(secretario[i], sizeof(tSecretario));
        fread(secretario[i], sizeof(tSecretario), 1, arquivo);
        
        secretario[i]->pessoa = RecuperaUmaPessoa(arquivo);
        secretario[i]->login = RecuperaLogin(arquivo);
    }
    
    return secretario;
}

void SalvaSecretarioBinario (tSecretario ** secretarios, int qtdSecretarios, char * path) {
    char dir[1001];
    sprintf(dir, "%s/secretarios.bin", path);
    FILE * arquivo = fopen(dir, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&qtdSecretarios, sizeof(int), 1, arquivo);
    for (int i = 0; i < qtdSecretarios; i++) {
        SalvaPessoa(secretarios[i]->pessoa, arquivo);
        SalvaLogin(secretarios[i]->login, arquivo);
    }

    fclose(arquivo);
}