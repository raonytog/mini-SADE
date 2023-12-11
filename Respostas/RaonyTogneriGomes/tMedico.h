#ifndef _TMEDICO_H_
#define _TMEDICO_H_

typedef struct tLogin tLogin;

#include "tLogin.h"
#include "tPessoa.h"

#include <stdbool.h>

typedef struct tMedico tMedico;

tMedico * CriaMedico ();

tMedico * CriaMedicoNULL ();

void DesalocaMedico(tMedico * medico);

bool ExisteMedicoCpf(tMedico ** medicos, int qtdMedicos, tMedico * medicoEmAnalise);

char * ObtemNomeMedico (tMedico * medico);

char * ObtemCRM (tMedico * medico);

char * ObtemMedicoCPF (tMedico * medico);

tLogin * ObtemMedicoLogin (tMedico * medico);

void SalvaMedico (tMedico * medico, FILE * arquivo);

tMedico ** RecuperaMedicos (FILE * arquivo, int * qtdMedicos);

void SalvaMedicoBinario (tMedico ** medicos, int qtdMedicos, char * path);

#endif