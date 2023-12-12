#ifndef _TMEDICO_H_
#define _TMEDICO_H_

typedef struct tLogin tLogin;

#include "tLogin.h"
#include "tPessoa.h"

#include <stdbool.h>

typedef struct tMedico tMedico;

/**
 * Cria e preenche um medico valido
*/
tMedico * CriaMedico ();

/**
 * Cria e preenche um medico com '\0'
*/
tMedico * CriaMedicoNULL ();

/**
 * Desaloca medico
*/
void DesalocaMedico(tMedico * medico);

/**
 * Verifica se o medico passado ja existe na lista de medicos
*/
bool ExisteMedicoCpf(tMedico ** medicos, int qtdMedicos, tMedico * medicoEmAnalise);

/**
 * Retorna o nome do medico 
*/
char * ObtemNomeMedico (tMedico * medico);

/**
 * Retorna o CRM do medico 
*/
char * ObtemCRM (tMedico * medico);

/**
 * Retorna o CPF do medico 
*/
char * ObtemMedicoCPF (tMedico * medico);

/**
 * Retorna o Login do medico 
*/
tLogin * ObtemMedicoLogin (tMedico * medico);


/**
 * Salva o medico no arquivo binario
*/
void SalvaMedico (tMedico * medico, FILE * arquivo);

/**
 *  Recupera a qtd e a lista de medicos do binario medicos.bin
*/
tMedico ** RecuperaMedicos (FILE * arquivo, int * qtdMedicos);

/**
 * Recupera um medico do arquivo
*/
tMedico * RecuperaUmMedico (FILE * arquivo);

/**
 * Salva todos os medicos no binario medico.bin
*/
void SalvaMedicoBinario (tMedico ** medicos, int qtdMedicos, char * path);

#endif