#ifndef _TLISTAPESSOAS_H_
#define _TLISTAPESSOAS_H_

#include "tPessoa.h"
#include "tListaPessoas.h"
#include "tFila.h"

typedef struct tListaPessoas tListaPessoas;

/**
 * Cria uma lista de busca vazia
*/
tListaPessoas * CriaListaBusca();

/**
 * Imprime o menu de busca de pacientes
*/
void ImprimeMenuBuscarPacientes (tFila * fila, tListaPessoas * lista);

/**
 * Obtem a pessoa da lista com o indice passado
*/
tPessoa * ObtemPessoaIndice (tListaPessoas * lista, int indice);

/**
 * Obtem o numero de pessoas na lista de busca
*/
int ObtemNumeroPessoasLista (tListaPessoas * lista);

/**
 * Adiciona uma pessoa na lista e a realloca no vetor
*/
void AdiconaPessoaLista (tListaPessoas * lista, tPessoa * pessoa);

/**
 * Desaloca lista de pessoas (sem desalocar as pessoas, apenas a estrutura)
*/
void DesalocaLista (void * data);

/**
 * Imprime a lista de busca na tela
*/
void ImprimeNomeRequisitadoTela (void * data);

/**
 * Imprime a lista de busca no arquivo
*/
void ImprimeNomeRequisitadoArquivo (void * data, char * path);

#endif