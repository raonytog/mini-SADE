#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct tPessoa tPessoa;

#include "tData.h"

#include <stdbool.h>

tPessoa * CriaPessoa ();

void DesalocaPessoa (void * dado);

bool ExistePessoaCpf(tPessoa ** pessoas, int qtdPessoas, tPessoa * pessoaEmAnalise);

bool EhCpfPessoa(tPessoa * pessoa, char * cpf);

tData * ObtemDataPessoa (tPessoa * pessoa);

char * ObtemNomePessoa (tPessoa * pessoa);

char * ObtemCPFPessoa (tPessoa * pessoa);

char * ObtemTelefonePessoa (tPessoa * pessoa);

char * ObtemGeneroPessoa (tPessoa * pessoa);

#endif
