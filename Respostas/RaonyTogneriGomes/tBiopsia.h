#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include "tLesao.h"
#include "tMedico.h"
#include "tPessoa.h"

typedef struct tBiopsia tBiopsia;

tBiopsia * CriaBiopsia (tPessoa * paciente, tLesao ** lesoes, int qtdLesoes, tMedico * medico, char *data);

void DesalocaBiopsia (tBiopsia * biopsia);

void ImprimeBiopsiaTela (tBiopsia * biopsia);

void ImprimeBiopsiaArquivo (tBiopsia * biopsia, FILE * arquivo);

int ObtemQtdLesoes (tBiopsia * biopsia);

tLesao * ObtemLesaoDoIndice (tBiopsia * biopsia, int indice);

tMedico * ObtemMedico (tBiopsia * biopsia);

tPessoa * ObtemPaciente (tBiopsia * biopsia);

#endif