#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct tPessoa tPessoa;

#include "tData.h"

#include <stdbool.h>

tPessoa * CriaPessoa ();

tPessoa * CriaPessoaNULL ();

void DesalocaPessoa (void * dado);

bool ExistePessoaCpf(tPessoa ** pessoas, int qtdPessoas, tPessoa * pessoaEmAnalise);

bool EhCpfPessoa(tPessoa * pessoa, char * cpf);

tData * ObtemDataPessoa (tPessoa * pessoa);

char * ObtemNomePessoa (tPessoa * pessoa);

char * ObtemCPFPessoa (tPessoa * pessoa);

char * ObtemTelefonePessoa (tPessoa * pessoa);

char * ObtemGeneroPessoa (tPessoa * pessoa);

void SalvaPessoa (tPessoa * pessoa, FILE * arquivo);

tPessoa ** RecuperaPessoas (FILE * arquivo, int * qtdPessoas);

tPessoa * RecuperaUmaPessoa (FILE * arquivo);

void SalvaPessoaBinario (tPessoa ** pessoas, int qtdPessoas, char * path);

#endif
