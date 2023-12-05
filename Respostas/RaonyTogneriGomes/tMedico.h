#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include "tPessoa.h"

typedef struct tMedico tMedico;

tMedico * CriaMedico (tPessoa * pessoa, char *CRM);

void DesalocaMedico(tMedico * medico);

const char * ObtemNomeMedico (tMedico * medico);

const char * ObtemCRM (tMedico * medico);

#endif