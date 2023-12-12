#ifndef _TRELATORIOGERAL_H_
#define _TRELATORIOGERAL_H_

#include "tConsulta.h"
#include "tPessoa.h"
#include "tFila.h"

typedef struct tRelatorioGeral tRelatorioGeral;

/**
 * Cria um relatorio e o preenche com as informacoes pertinentes
*/
tRelatorioGeral * CriaRelatorioGeral (tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, int qtdConsultas);

/**
 * Executa o sistema do relatorio
 * 1 - insere insere relatorio na fila
 * 2 - sai
*/
void ExecutaRelatorioGeral (tFila * fila, tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, 
                            int qtdConsultas, char * pathSaida);

/**
 * Imprime o relatorio na tela
*/
void ImprimeRelatorioGeralTela (void * data);

/**
 * Imprime o relatorio no arquivo
*/
void ImprimeRelatorioGeralArquivo (void * data, char * path);

/**
 * Desaloca o relatorio
*/
void DesalocaRelatorioGeral (void * data);

/**
 * Calcula a idade media das pessoas do SADE
*/
int CalculaMediaIdadeRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

/**
 * Retorna qts das pessoas sao mulheres
*/
int RetornaQtdMulheresRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

/**
 * Retorna qts das pessoas sao homens
*/
int RetornaQtdHomensRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

/**
 * Retorna qts das pessoas sao de outro genero
*/
int RetornaQtdOutrosRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

/**
 * Retorna qtd de pessoas atendidas pelo SADE (inclui banco de dados)
*/
int RetornaQtdPessoasAtentidas (tPessoa ** pessoas, int qtdPessoas);

/**
 * Retorna a media do tamanho das lesoes consultadas
*/
int TamanhoMedioLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

/**
 * Retorna a qtd de lesoes que precisaram de cirurgia
*/
int RetornaQtdCirurgiasRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

/**
 * Retorna a qtd de lesoes que precisaram de crioterapia
*/
int RetornaQtdCrioterapiaRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

/**
 * Retorna a qtd de lesoes totais das consultas
*/
int RetornaQtdLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

/**
 * Calcula a idade das pessoas, levando em base o dia 09/11/2023
*/
int CalculaIdade(tPessoa * pessoa);

#endif // !_TRELATORIOGERAL_H_

