#include "tLesao.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tLesao {
    int rotulo;
    char diagnosticoClinico[20];
    char regiaoDoCorpo[20];

    int tamanhoLesao;         //em milimetros
    int necessitaCirurgia;    // true or false
    int necessitaCrioterapia; //true or false
};

tLesao * CriaLesao (int rotulo, char * diagnosticoClinico, char * regiaoDoCorpo, int tamLesao, int precisaCirurgia, int precisaCrioterapia) {
    tLesao * lesao = calloc(1, sizeof(tLesao));
    if (!lesao) return NULL;
    
    lesao->rotulo = rotulo;
    strcpy(lesao->diagnosticoClinico, diagnosticoClinico);
    strcpy(lesao->regiaoDoCorpo, regiaoDoCorpo);

    lesao->tamanhoLesao = tamLesao;
    lesao->necessitaCirurgia = precisaCirurgia;
    lesao->necessitaCrioterapia = precisaCrioterapia;
    
    return lesao;
}

void ImprimeLesaoTela (tLesao * lesao) {
    if (!lesao) return;
    printf("L%d - %s - %s - %dMM\n", 
            lesao->rotulo, lesao->diagnosticoClinico, lesao->regiaoDoCorpo, lesao->tamanhoLesao);
}

void ImprimeLesaoArquivo (tLesao * lesao, FILE * arquivo) {
    fprintf(arquivo, "L%d - %s - %s - %dMM\n", 
             lesao->rotulo, lesao->diagnosticoClinico, lesao->regiaoDoCorpo, lesao->tamanhoLesao);
}

void DesalocaLesao (tLesao * lesao) {
    if (!lesao) return;
    free(lesao);
    lesao = NULL;
}

int ObtemRotulo (tLesao * lesao) {
    if (!lesao) return 0;
    return lesao->rotulo;
}

char * ObtemDiagnostico (tLesao * lesao) {
    if (!lesao) return NULL;
    char * diagnostico = lesao->diagnosticoClinico;
    return diagnostico;
}

char * ObtemRegiaoCorpo (tLesao * lesao) {
    if (!lesao) return NULL;
    char * regiao = lesao->regiaoDoCorpo;
    return regiao;
}

int NecessitaCirurgia (tLesao * lesao) {
    if (!lesao) return 0;
    return lesao->necessitaCirurgia;
}

int NecessitaCrioterapia (tLesao * lesao) {
    if (!lesao) return 0;
    return lesao->necessitaCrioterapia;
}

int ObtemTamanhoLesao (tLesao * lesao) {
    if (!lesao) return 0;
    return lesao->tamanhoLesao;
}