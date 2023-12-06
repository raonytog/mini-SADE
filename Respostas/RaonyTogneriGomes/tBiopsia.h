#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include "tLesao.h"
#include "tMedico.h"
#include "tPessoa.h"

typedef struct tBiopsia tBiopsia;

tBiopsia * CriaBiopsia (char * nomePaciente, char * CPF, tLesao ** lesoes, int qtdLesoes, 
                        char *nomeMedico, char *CRM, char *data);

void DesalocaBiopsia (tBiopsia * biopsia);

void ImprimeBiopsiaTela (void * data);

void ImprimeBiopsiaArquivo (void * data, char * path);

int ObtemQtdLesoes (tBiopsia * biopsia);

tLesao * ObtemLesaoDoIndice (tBiopsia * biopsia, int indice);

#endif