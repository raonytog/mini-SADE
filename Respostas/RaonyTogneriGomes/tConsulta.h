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

tConsulta * CriaConsulta ();

void DesalocaConsulta (tConsulta * consulta);

void ExecutaConsulta (tConsulta * consulta, tFila * fila, int EhMedico);

void ImprimeErroConsulta (char * cpf);


void LeReceitaConsulta (tConsulta * consulta, tFila * fila);

void LeLesaoConsulta (tConsulta * consulta);

void LeBiopsiaConsulta (tConsulta * consulta, tFila * fila);

void LeEncaminhamentoConsulta (tConsulta * consulta, tFila * fila);


int RetornaQtdLesoesConsulta (tConsulta * consulta);

int RetornaPrecisaDeCirurgiaConsulta (tConsulta * consulta);

int RetornaPrecisaDeCrioterapiaConsulrta (tConsulta * consulta);

int RetornaTamanhoLesaoConsulta (tConsulta * consulta, int indice);

void SalvaConsultaBinario (tConsulta ** consultas, int qtdConsultas, char * path);

#endif 