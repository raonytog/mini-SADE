#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include "tListaPessoas.h"
#include "tLesao.h"

#include <stdbool.h>

typedef struct tConsulta tConsulta;

tConsulta * CriaConsulta ();

void DesalocaConsulta (tConsulta * consulta);

bool EstaCadastradoPacienteCpf (tListaPessoas * lista, char * cpf);

void ImprimeMenuConsulta ();

void LeReceitaConsulta (tConsulta * consulta);

void LeLesaoConsulta (tConsulta * consulta);

void LeBiopsiaConsulta (tConsulta * consulta);

void LeEncaminhamentoConsulta (tConsulta * consulta);

#endif 