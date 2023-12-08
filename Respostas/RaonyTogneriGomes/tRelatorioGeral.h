#ifndef _TRELATORIOGERAL_H_
#define _TRELATORIOGERAL_H_

#include "tLesao.h"
#include "tPessoa.h"
#include "tFila.h"

typedef struct tRelatorioGeral tRelatorioGeral;

tRelatorioGeral * CriaRelatorioGeral (tPessoa ** pessoas, int qtdPessoas, 
                                      tLesao ** lesoes, int qtdLesoes, int qtdConsultas);

void ExecutaRelatorioGeral (tFila * fila, tPessoa ** pessoas, int qtdPessoas, tLesao ** lesoes, 
                            int qtdLesoes, int qtdConsultas, char * pathSaida);

void ImprimeRelatorioGeralTela (void * data);

void ImprimeRelatorioGeralArquivo (void * data, char * path);

void DesalocaRelatorioGeral (void * data);

int CalculaMediaIdade (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdMulheres (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdHomens (tPessoa ** pessoas, int qtdPessoas);

int RetornaQtdOutros (tPessoa ** pessoas, int qtdPessoas);

int TamanhoMedioLesoes (tLesao ** lesoes, int qtdLesoes);

int RetornaQtdCirurgias (tLesao ** lesoes, int qtdLesoes);

int RetornaQtdCrioterapia (tLesao ** lesoes, int qtdLesoes);

#endif // !_TRELATORIOGERAL_H_

