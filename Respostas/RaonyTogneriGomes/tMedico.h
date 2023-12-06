#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include "tLogin.h"
#include "tPessoa.h"

typedef struct tMedico tMedico;

tMedico * CriaMedico ();

void DesalocaMedico(tMedico * medico);

const char * ObtemNomeMedico (tMedico * medico);

const char * ObtemCRM (tMedico * medico);

tLogin * ObtemLoginMedico (tMedico * medico);

#endif