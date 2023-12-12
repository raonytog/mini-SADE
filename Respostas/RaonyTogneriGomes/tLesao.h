#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>

typedef struct tLesao tLesao;

/**
 * Cria uma lesao valida com as informacoes dos parametros
*/
tLesao * CriaLesao (int rotulo, char * diagnosticoClinico, char * regiaoDoCorpo, int tamLesao, int precisaCirurgia, int precisaCrioterapia);

/**
 * Imprime as informacoes da lesao na tela
*/
void ImprimeLesaoTela (tLesao * lesao);

/**
 * Imprime as informacoes da lesao no arquivo
*/
void ImprimeLesaoArquivo (tLesao * lesao, FILE * arquivo);

/**
 * Desaloca a lesao
*/
void DesalocaLesao (tLesao * lesao);

/**
 * Obtem o rotulo da lesao
*/
int ObtemRotulo (tLesao * lesao);

/**
 * Obtem o diagnostico da lesao
*/
char * ObtemDiagnostico (tLesao * lesao);

/**
 * Obtem a regiao do corpo em que ocorreu a lesao
*/
char * ObtemRegiaoCorpo (tLesao * lesao);

/** 
 * retorna se precisa de cirurgia
*/
int NecessitaCirurgia (tLesao * lesao);

/**
 * retorna se precisa de crioterapia
*/
int NecessitaCrioterapia (tLesao * lesao);

/**
 * Retorna o tamanho da lesao
*/
int ObtemTamanhoLesao (tLesao * lesao);

/**
 * Salva a lesao no arquivo
*/
void SalvaLesao (tLesao * lesao, FILE * arquivo);

/**
 * Recupera uma lesao do arquivo
*/
tLesao * RecuperaLesao (FILE * arquivo);

/**
 * Salva as lesoes no arquivo 
*/
void SalvaLesaoBinario (tLesao ** lesoes, int qtdLesoes, char * path);

#endif
