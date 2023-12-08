#ifndef _TMEDICO_H_
#define _TMEDICO_H_

typedef struct tLogin tLogin;

#include "tLogin.h"
#include "tPessoa.h"

#include <stdbool.h>

typedef struct tMedico tMedico;

tMedico * CriaMedico ();

void DesalocaMedico(tMedico * medico);

bool ExisteMedicoCpf(tMedico ** medicos, int qtdMedicos, tMedico * medicoEmAnalise);

char * ObtemNomeMedico (tMedico * medico);

char * ObtemCRM (tMedico * medico);

char * ObtemMedicoCPF (tMedico * medico);

tLogin * ObtemMedicoLogin (tMedico * medico);

#endif