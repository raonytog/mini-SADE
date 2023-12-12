#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct tPessoa tPessoa;

#include <stdbool.h>
#include <stdio.h>

/** 
 * Cria e e preenche as informacoes passadas pelo terminal para uma pessoa valida
*/
tPessoa * CriaPessoa ();

/**
 * Cria uma pessoa totalmente inciializada com '\0' 
*/
tPessoa * CriaPessoaNULL ();

/**
 * Desaloca uma pessoa valida
*/
void DesalocaPessoa (void * dado);

/**
 * Verifica se a pessoa em analise tem o mesmo cpf de alguma da lista de pessoa
*/
bool ExistePessoaCpf(tPessoa ** pessoas, int qtdPessoas, tPessoa * pessoaEmAnalise);

/**
 * Verifica se o dado cpf é da pessoa passada
*/
bool EhCpfPessoa(tPessoa * pessoa, char * cpf);

/**
 * Obtem a data da pessoa em string
*/
char * ObtemDataPessoa (tPessoa * pessoa);

/**
 * Obtem o nome da pessoa
*/
char * ObtemNomePessoa (tPessoa * pessoa);

/**
 * Obtem o cpf da pessoa
*/
char * ObtemCPFPessoa (tPessoa * pessoa);

/**
 * Obtem o telefone da pessoa
*/
char * ObtemTelefonePessoa (tPessoa * pessoa);

/**
 * Obtem o genero da pessoa
*/
char * ObtemGeneroPessoa (tPessoa * pessoa);

/**
 * Obtem se o paciente ja foi atendido
*/
int ObtemSeFoiAtendido (tPessoa * pessoa);

/** 
 * Obtem o dia de nascimento da pessoa
*/
int ObtemDiaPessoa (tPessoa * pessoa);

/**
 * Obtem o mes de nascimento da pessoa
*/
int ObtemMesPessoa (tPessoa * pessoa);

/**
 * Obtem o ano de nascimento da pessoa
*/
int ObtemAnoPessoa (tPessoa * pessoa);

/**
 * Atualiza a pessoa como atendida
*/
void AtualizaPessoaComoAtendida (tPessoa * pessoa);

/**
 * Salva a pessoa no arquivo binario
*/
void SalvaPessoa (tPessoa * pessoa, FILE * arquivo);


/**
 * Recupera a lista de pessoas, tal como a qtd delas, do arquivo binario pessoas.bin
*/
tPessoa ** RecuperaPessoas (FILE * arquivo, int * qtdPessoas);

/**
 * Recupera uma pessoa do arquivo binario informado
*/
tPessoa * RecuperaUmaPessoa (FILE * arquivo);

/**
 * Salva a qtd de pessoas e a lista de pessoas no caminho passado, gerando o arquivo binario
*/
void SalvaPessoaBinario (tPessoa ** pessoas, int qtdPessoas, char * path);



#endif
