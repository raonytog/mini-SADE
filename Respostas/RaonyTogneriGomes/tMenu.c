#include "tMenu.h"

#include <stdio.h>

void ImprimeMenuAdmin () {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR SECRETARIO\n");
    printf("\t(2) CADASTRAR MEDICO\n");
    printf("\t(3) CADASTRAR PACIENTE\n");
    printf("\t(4) REALIZAR CONSULTA\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

void ImprimeMenuUser () {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(2) CADASTRAR MEDICO\n");
    printf("\t(3) CADASTRAR PACIENTE\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

void ImprimeMenuMedico () {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(4) REALIZAR CONSULTA\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

void ImprimeMenu(CARGO_LOGADO cargo) {
    switch (cargo) {
        case ADMIN:
            ImprimeMenuAdmin();
            break;

        case MEDICO:
            ImprimeMenuMedico();
            break;

        case USER:
            ImprimeMenuUser();
            break;

        case FALHA:
            break;
    }
}

void ImprimeMenuConsulta () {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
	printf("\t(1) CADASTRAR LESAO\n");
	printf("\t(2) GERAR RECEITA MEDICA\n");
	printf("\t(3) SOLICITACAO DE BIOPSIA\n");
	printf("\t(4) ENCAMINHAMENTO\n");
	printf("\t(5) ENCERRAR CONSULTA\n");
    printf("############################################################\n");
}

void ImprimeMenuRelatorio () {
    printf("\nESCOLHA UMA OPCAO:\n");
    printf("(1) ENVIAR PARA IMPRESSAO\n");
    printf("(2) RETORNAR AO MENU PRINCIPAL\n");
    printf("############################################################\n");
}


void ImprimeMenuFilaImpressao () {
    printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("(1) EXECUTAR FILA DE IMPRESSAO\n");
    printf("(2) RETORNAR AO MENU PRINCIPAL\n");
    printf("############################################################\n");
}