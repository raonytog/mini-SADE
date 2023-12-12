#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include "tLesao.h"
#include "tMedico.h"
#include "tPessoa.h"

typedef struct tBiopsia tBiopsia;

/**
 * Retorna uma biopsia valida, de acordo com os parametros passados
*/
tBiopsia * CriaBiopsia (char * nomePaciente, char * CPF, tLesao ** lesoes, int qtdLesoes, 
                        char *nomeMedico, char *CRM, char *data);

/** 
 * Desaloca uma biopsia, caso exista
*/
void DesalocaBiopsia (void * data);

/**
 * Imprime a biopsia na tela
*/
void ImprimeBiopsiaTela (void * data);

/**
 * Imprime biopsia no arquivo
*/
void ImprimeBiopsiaArquivo (void * data, char * path);

/**
 * Obtem a qtd de lesoes da biopsia
*/
int ObtemQtdLesoes (tBiopsia * biopsia);

/**
 * Obtem a lesao do indice N pertencente a biopsia
*/
tLesao * ObtemLesaoDoIndice (tBiopsia * biopsia, int indice);

#endif