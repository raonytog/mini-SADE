#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include "tLogin.h"
#include "tPessoa.h"

typedef struct tMedico tMedico;

tMedico * CriaMedico ();

void DesalocaMedico(tMedico * medico);

char * ObtemNomeMedico (tMedico * medico);

char * ObtemCRM (tMedico * medico);

char * ObtemMedicoCPF (tMedico * medico);

#endif