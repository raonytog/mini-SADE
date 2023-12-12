#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include "tLesao.h"
#include "tFila.h"

#include <stdbool.h>

typedef struct tConsulta tConsulta;

typedef enum {
    CADASTRAR_LESAO = 1,
    GERAR_RECEITA_MEDICA = 2,
    SOLICITACAO_DE_BIOPSIA = 3,
    ENCAMINHAMENTO = 4,
    ENCERRAR_CONSULTA =5
} OPCOES_CONSULTA;


/**
 * Cria a consulta, lendo as informacoes necessarias
*/
tConsulta * CriaConsulta ();

/**
 * Desaloca a consulta
*/
void DesalocaConsulta (tConsulta * consulta);

/**
 * Executa o loop das possibilidades de realizar dentro da consulta
*/
void ExecutaConsulta (tConsulta * consulta, tFila * fila, int EhMedico);


/**
 * Imprime erro na consulta (paciente sem cadastro);
*/
void ImprimeErroConsulta (char * cpf);

/**
 * Le a receita da consulta e manda para a fila, caso peca
*/
void LeReceitaConsulta (tConsulta * consulta, tFila * fila);

/**
 * Le a lesao da consulta e manda para a fila, caso peca
*/
void LeLesaoConsulta (tConsulta * consulta);

/**
 * Le a biopsia da consulta e manda para a fila, caso peca
*/
void LeBiopsiaConsulta (tConsulta * consulta, tFila * fila);

/**
 * Le o encaminhamento da consulta e manda para a fila, caso peca
*/
void LeEncaminhamentoConsulta (tConsulta * consulta, tFila * fila);

/**
 * Retorna a qtd de lesoes da consulta
*/
int RetornaQtdLesoesConsulta (tConsulta * consulta);

/**
 * Retorna a quantidade de lesoes que precisaram de cirurgia nesta consulta
*/
int RetornaPrecisaDeCirurgiaConsulta (tConsulta * consulta);

/**
 * Retorna a quantidade de lesoes que precisaram de crioterapia nesta consulta
*/
int RetornaPrecisaDeCrioterapiaConsulrta (tConsulta * consulta);

/**
 * Retorna tamanho da lesao da consulta no indice passado
*/
int RetornaTamanhoLesaoConsulta (tConsulta * consulta, int indice);

/**
 * Salva a consulta no arquivo binario consultas.bin
*/
void SalvaConsultaBinario (tConsulta ** consultas, int qtdConsultas, char * path);

/**
 * Salva a consulta no arquivo binario 
*/
void SalvaConsulta (tConsulta * tConsulta, FILE * arquivo);

/**
 * Recupera as consultas do arquivo binario consultas.bin
*/
tConsulta ** RecuperaConsulta (FILE * arquivo, int * qtdConsultas);

#endif 