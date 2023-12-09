#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>

typedef struct tLesao tLesao;

tLesao * CriaLesao (int rotulo, char * diagnosticoClinico, char * regiaoDoCorpo, int tamLesao, int precisaCirurgia, int precisaCrioterapia);

void ImprimeLesaoTela (tLesao * lesao);

void ImprimeLesaoArquivo (tLesao * lesao, FILE * arquivo);

void DesalocaLesao (tLesao * lesao);


int ObtemRotulo (tLesao * lesao);

char * ObtemDiagnostico (tLesao * lesao);

char * ObtemRegiaoCorpo (tLesao * lesao);

int NecessitaCirurgia (tLesao * lesao);

int NecessitaCrioterapia (tLesao * lesao);

int ObtemTamanhoLesao (tLesao * lesao);

#endif
