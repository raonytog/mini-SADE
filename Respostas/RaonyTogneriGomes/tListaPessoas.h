#ifndef _TLISTAPESSOAS_H_
#define _TLISTAPESSOAS_H_

#include "tPessoa.h"

typedef struct tListaPessoas tListaPessoas;

tListaPessoas * CriaListaBusca();

void ImprimeMenuBuscarPacientes ();

tPessoa * ObtemPessoaIndice (tListaPessoas * lista, int indice);

int ObtemNumeroPessoasLista (tListaPessoas * lista);

void AdiconaPessoaLista (tListaPessoas * lista, tPessoa * pessoa);

void DesalocaLista (tListaPessoas * lista);

void ImprimeNomeRequisitadoTela (void * data);

void ImprimeNomeRequisitadoArquivo (void * data, char * path);

#endif