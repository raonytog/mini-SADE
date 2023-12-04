//L1 - NEVO - DORSO - 10MM

#include "tLesao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tLesao {
    char rotulo[5];
    char diagnosticoClinico[20];
    char regiaoDoCorpo[20];

    int tamanhoLesao; //em milimetros
    int necessitaCirurgia;
    int necessitaCrioterapia;
};

tLesao * CriaLesao () {
    tLesao * lesao = malloc(sizeof(tLesao));
    lesao->rotulo[0] = '\0';
    lesao->diagnosticoClinico[0] = '\0';
    lesao->regiaoDoCorpo[0] = '\0';

    lesao->tamanhoLesao = 0;
    lesao->necessitaCirurgia = 0;
    lesao->necessitaCrioterapia = 0;

    scanf("%s%*c", lesao->rotulo);
    scanf("%s%*c", lesao->diagnosticoClinico);
    scanf("%s%*c", lesao->regiaoDoCorpo);
    scanf("%d%*c", lesao->tamanhoLesao);

    return lesao;
}

void ImprimeLesaoTela (tLesao * lesao) {
    printf("L%s - %s - %s - %dMM\n", lesao->rotulo, lesao->diagnosticoClinico, lesao->regiaoDoCorpo, lesao->tamanhoLesao);
}

void ImprimeLesaoArquivo (tLesao * lesao, char * path) {
    // pendente
}

void DesalocaLesao (tLesao * lesao) {
    free(lesao);
}

int NecessitaCirurgia (tLesao * lesao) {
    return lesao->necessitaCirurgia;
}

int NecessitaCrioterapia (tLesao * lesao) {
    return lesao->necessitaCrioterapia;
}

int TamanhoLesao (tLesao * lesao) {
    return lesao->tamanhoLesao;
}