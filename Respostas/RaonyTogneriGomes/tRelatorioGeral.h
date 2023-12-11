#ifndef _TRELATORIOGERAL_H_
#define _TRELATORIOGERAL_H_

#include "tConsulta.h"
#include "tPessoa.h"
#include "tFila.h"

typedef struct tRelatorioGeral tRelatorioGeral;

tRelatorioGeral * CriaRelatorioGeral (tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, int qtdConsultas);

void ExecutaRelatorioGeral (tFila * fila, tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, 
                            int qtdConsultas, char * pathSaida);

void ImprimeRelatorioGeralTela (void * data);

void ImprimeRelatorioGeralArquivo (void * data, char * path);

void DesalocaRelatorioGeral (void * data);

int CalculaMediaIdadeRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdMulheresRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdHomensRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdOutrosRelatorioGeral (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdPessoasAtentidas (tPessoa ** pessoas, int qtdPessoas);

int TamanhoMedioLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

int RetornaQtdCirurgiasRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

int RetornaQtdCrioterapiaRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

int RetornaQtdLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas);

#endif // !_TRELATORIOGERAL_H_

