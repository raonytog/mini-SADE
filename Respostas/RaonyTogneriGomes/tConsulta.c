#include "tConsulta.h"
#include "tData.h"
#include "tPessoa.h"
#include "tMedico.h"
#include "tFila.h"
#include "tDocumento.h"

#include "tLesao.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tConsulta {
    tPessoa * paciente;
    tMedico * medico;
    tData * dataConsulta;

    tLesao ** lesao;
    tReceita ** receita;
    tBiopsia * biopsia;
    tEncaminhamento ** encaminhamento;
    int qtdLesoes, qtdReceitas, qtdEncaminhamentos;
    
    int diabetico, fumante, alergico, historicoCancerigeno;
    char tipoPele[2];
};

tConsulta * CriaConsulta (tPessoa * pessoa, tMedico * medico) {
    
    tConsulta * consulta = malloc(sizeof(tConsulta));
    if (!consulta) return NULL;
 
    consulta->paciente = pessoa;
    consulta->medico = medico;

    consulta->qtdEncaminhamentos = 0;
    consulta->qtdLesoes = 0;
    consulta->qtdReceitas = 0;

    consulta->dataConsulta = LeDataConsulta();;

    printf("POSSUI DIABETES: ");                    scanf("%d",  &consulta->diabetico);
    printf("FUMANTE: ");                            scanf("%d",  &consulta->fumante);
    printf("ALERGIA A MEDICAMENTO: ");              scanf("%d",  &consulta->alergico);
    printf("HISTORICO DE CANCER: ");                scanf("%d",  &consulta->historicoCancerigeno);
    printf("TIPO DE PELE: ");                       scanf("%[^\n]%*c",  consulta->tipoPele);
    printf("############################################################\n");

    return consulta;
}

void DesalocaConsulta (tConsulta * consulta) {
    if (!consulta) return;

    DesalocaPessoa(consulta->paciente);
    DesalocaMedico(consulta->medico);
    DesalocaData(consulta->dataConsulta);

    for (int i = 0; i < consulta->qtdLesoes; i++) 
        DesalocaLesao(consulta->lesao[i]);
    free(consulta->lesao);

    free(consulta);
}

void ImprimeMenuConsulta () {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO: ");
	printf("\t(1) CADASTRAR LESAO\n");
	printf("\t(2) GERAR RECEITA MEDICA\n");
	printf("\t(3) SOLICITACAO DE BIOPSIA\n");
	printf("\t(4) ENCAMINHAMENTO\n");
	printf("\t(5) ENCERRAR CONSULTA\n");
    printf("############################################################\n");
}

void ExecutaConsulta (tConsulta * consulta) {
    int opcao = 0;
    while (1) {
        scanf("%d%*c", &opcao);
        switch (opcao) {
            case CADASTRAR_LESAO:
                break;

            case GERAR_RECEITA_MEDICA:
                break;

            case SOLICITACAO_DE_BIOPSIA:
                break;

            case ENCAMINHAMENTO:
                break;

            case ENCERRAR_CONSULTA:
                return;
                break;
        
        }
    }
}

void ImprimeErroConsulta (char * cpf) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: %s\n", cpf);
    printf("PACIENTE SEM CADASTRO\n");
    printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
}

void LeReceitaConsulta (tConsulta * consulta, tFila * fila) {
    eTipoUso tipo;
    int qtdMedicamento = 0;
    char tipoUso[6], nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO], instrucoes[300];
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("RECEITA MEDICA:\n");
    printf("TIPO DE USO: ");                    scanf("%[^\n]%*c", tipoUso);
    printf("NOME DO MEDICAMENTO: ");            scanf("%[^\n]%*c", nomeMedicamento);
    printf("TIPO DO MEDICAMENTO: ");            scanf("%[^\n]%*c", tipoMedicamento);
    printf("QUANTIDADE: ");                     scanf("%d", &qtdMedicamento);
    printf("INSTRUCOES DE USO: ");              scanf("%[\n]%*c", instrucoes);
    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c");

    if (strcmp(tipoUso, "ORAL") == 0)
        tipo = ORAL;
    
    else if (strcmp(tipoUso, "TOPICO") == 0)
        tipo = TOPICO;

    (consulta->qtdReceitas)++;
    consulta->receita = realloc(consulta->receita, consulta->qtdReceitas * sizeof(tReceita *));
    consulta->receita[consulta->qtdReceitas-1] = criaReceita( ObtemNomePessoa(consulta->paciente), tipo, nomeMedicamento, tipoMedicamento, 
                                                 instrucoes, qtdMedicamento, ObtemNomeMedico(consulta->medico), ObtemCRM(consulta->medico), 
                                                 ObtemDataString(consulta->dataConsulta) );

    tDocumento * doc = criaDocumento(consulta->receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    insereDocumentoFila(fila, doc, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
}

void LeLesaoConsulta (tConsulta * consulta) {
    char diagonostico[20], regiao[20];
    int tamanho, cirurgia, crioterapia;
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");
    printf("DIAGONISTICO CLINICO: ");               scanf("%[^\n]%*c", diagonostico);
    printf("REGIAO DO CORPO: ");                    scanf("%[^\n]%*c", regiao);
    printf("TAMANHO: ");                            scanf("%d", &tamanho);
    printf("ENVIAR PARA CIRURGIA: ");               scanf("%d", &cirurgia);
    printf("ENVIAR PARA A CRIOTERAPIA: ");          scanf("%d", &crioterapia);
    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c");

    (consulta->qtdLesoes)++;
    consulta->lesao = realloc(consulta->lesao, consulta->qtdLesoes * sizeof(tLesao *));
    consulta->lesao[consulta->qtdLesoes-1] = CriaLesao(consulta->qtdLesoes, diagonostico, regiao, tamanho);
}

void LeBiopsiaConsulta (tConsulta * consulta, tFila * fila) {
    int precisa = 0;
    for (int i = 0; i < consulta->qtdLesoes; i++) 
        if (NecessitaCirurgia(consulta->lesao[i])) precisa++;
    
    if (!precisa) return;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("#################### CONSULTA MEDICA #######################\n");
    scanf("%*c");
    tDocumento * doc = criaDocumento(consulta->biopsia, ImprimeBiopsiaTela, ImprimeBiopsiaArquivo, DesalocaBiopsia);
    insereDocumentoFila(fila, doc, ImprimeBiopsiaTela, ImprimeBiopsiaArquivo, DesalocaBiopsia);
}

void LeEncaminhamentoConsulta (tConsulta * consulta, tFila * fila) {
    char especialidade[50], motivo[300];
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ENCAMINHAMENTO:\n"); 
    printf("ESPECIALIDADE ENCAMINHADA: ");          scanf("%[^\n]%*c", especialidade);
    printf("MOTIVO: ");                             scanf("%[^\n]%*c", motivo);
    printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR");
    printf("############################################################\n");
    scanf("%*c");

    (consulta->qtdEncaminhamentos)++;
    consulta->encaminhamento = realloc (consulta->encaminhamento, consulta->qtdEncaminhamentos * sizeof(tEncaminhamento *));
    consulta->encaminhamento[consulta->qtdEncaminhamentos-1] = CriaEncaminhamento(ObtemNomePessoa(consulta->paciente), ObtemCPFPessoa(consulta->paciente), 
                                                               especialidade, motivo, ObtemNomeMedico(consulta->medico), ObtemCRM(consulta->medico), 
                                                               ObtemDataString(consulta->dataConsulta));
}