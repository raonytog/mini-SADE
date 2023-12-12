#ifndef _TMENU_H_
#define _TMENU_H_

#include "tLogin.h"

/**
 * opcoes disponiveis nos menus principais
*/
typedef enum {
    CADASTRAR_SECRETARIO = 1,
    CADASTRAR_MEDICO = 2,
    CADASTRAR_PACIENTE = 3,
    REALIZAR_CONSULTA = 4,
    BUSCAR_PACIENTES = 5,
    RELATORIO_GERAL = 6,
    FILA_DE_IMPRESSAO = 7,
    FINALIZAR_O_PROGRAMA = 8
} OPCOES_MENU;

void ImprimeMenuAdmin ();

void ImprimeMenuUser ();

void ImprimeMenuMedico ();

/**
 * Imprime o menu de acordo com o cargo logado
*/
void ImprimeMenu(CARGO_LOGADO cargo);

void ImprimeMenuConsulta ();

void ImprimeMenuRelatorio ();

void ImprimeMenuFilaImpressao ();

#endif