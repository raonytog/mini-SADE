#ifndef _TLISTAPESSOAS_H_
#define _TLISTAPESSOAS_H_

#include "tPessoa.h"

typedef struct tListaPessoas tListaPessoas;

tListaPessoas * CriaListaBusca();

void AdiconaPessoaLista (tListaPessoas ** lista, tPessoa * pessoa);

void DesalocaLista (tListaPessoas ** lista);

#endif