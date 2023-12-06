#ifndef _TLISTAPESSOAS_H_
#define _TLISTAPESSOAS_H_

#include "tPessoa.h"

typedef struct tListaPessoas tListaPessoas;

tListaPessoas * CriaListaBusca();

int ObtemNumeroPessoasLista (tListaPessoas * lista);

void AdiconaPessoaLista (tListaPessoas * lista, tPessoa * pessoa, char * nome);

void DesalocaLista (tListaPessoas * lista);

void ImprimeNomeRequisitadoTela (tListaPessoas * lista, char * nome);

void ImprimeNomeRequisitadoArquivo (tListaPessoas * lista, char * nome, char * path);

#endif