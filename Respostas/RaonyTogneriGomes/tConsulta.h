#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include "tLesao.h"
#include "tFila.h"
#include "tListaPessoas.h"

#include <stdbool.h>

typedef struct tConsulta tConsulta;

tConsulta * CriaConsulta ();

void DesalocaConsulta (tConsulta * consulta);

bool EstaCadastradoPacienteCpf (tListaPessoas * lista, char * cpf);

void ImprimeMenuConsulta ();

void LeReceitaConsulta (tConsulta * consulta, tFila * fila);

void LeLesaoConsulta (tConsulta * consulta);

void LeBiopsiaConsulta (tConsulta * consulta, tFila * fila);

void LeEncaminhamentoConsulta (tConsulta * consulta, tFila * fila);

#endif 