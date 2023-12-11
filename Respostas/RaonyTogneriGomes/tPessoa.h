#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct tPessoa tPessoa;

#include <stdbool.h>
#include <stdio.h>

tPessoa * CriaPessoa ();

tPessoa * CriaPessoaNULL ();

void DesalocaPessoa (void * dado);

bool ExistePessoaCpf(tPessoa ** pessoas, int qtdPessoas, tPessoa * pessoaEmAnalise);

bool EhCpfPessoa(tPessoa * pessoa, char * cpf);

char * ObtemDataPessoa (tPessoa * pessoa);

char * ObtemNomePessoa (tPessoa * pessoa);

char * ObtemCPFPessoa (tPessoa * pessoa);

char * ObtemTelefonePessoa (tPessoa * pessoa);

char * ObtemGeneroPessoa (tPessoa * pessoa);

int ObtemSeFoiAtendido (tPessoa * pessoa);

int ObtemDiaPessoa (tPessoa * pessoa);

int ObtemMesPessoa (tPessoa * pessoa);

int ObtemAnoPessoa (tPessoa * pessoa);

void SalvaPessoa (tPessoa * pessoa, FILE * arquivo);

void AtualizaPessoaComoAtendida (tPessoa * pessoa);


tPessoa ** RecuperaPessoas (FILE * arquivo, int * qtdPessoas);

tPessoa * RecuperaUmaPessoa (FILE * arquivo);

void SalvaPessoaBinario (tPessoa ** pessoas, int qtdPessoas, char * path);



#endif
