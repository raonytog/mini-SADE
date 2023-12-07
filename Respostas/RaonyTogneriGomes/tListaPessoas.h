#ifndef _TLISTAPESSOAS_H_
#define _TLISTAPESSOAS_H_

#include "tPessoa.h"
#include "tListaPessoas.h"
#include "tFila.h"

typedef struct tListaPessoas tListaPessoas;

tListaPessoas * CriaListaBusca();

void ImprimeMenuBuscarPacientes (tFila * fila, tListaPessoas * lista);

tPessoa * ObtemPessoaIndice (tListaPessoas * lista, int indice);

int ObtemNumeroPessoasLista (tListaPessoas * lista);

void AdiconaPessoaLista (tListaPessoas * lista, tPessoa * pessoa);

void DesalocaLista (void * data);

void ImprimeNomeRequisitadoTela (void * data);

void ImprimeNomeRequisitadoArquivo (void * data, char * path);

#endif