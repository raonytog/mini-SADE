#include "tConsulta.h"
#include "tData.h"
#include "tPessoa.h"
#include "tMedico.h"
#include "tFila.h"
#include "tDocumento.h"
#include "tMenu.h"

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

    printf("POSSUI DIABETES: ");                    scanf("%d%*c",  &consulta->diabetico);
    printf("FUMANTE: ");                            scanf("%d%*c",  &consulta->fumante);
    printf("ALERGIA A MEDICAMENTO: ");              scanf("%d%*c",  &consulta->alergico);
    printf("HISTORICO DE CANCER: ");                scanf("%d%*c",  &consulta->historicoCancerigeno);
    printf("TIPO DE PELE: ");                       scanf("%[^\n]%*c",  consulta->tipoPele);
    printf("\n############################################################\n");

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

void ExecutaConsulta (tConsulta * consulta, tFila * fila) {
    char tipo[7], 
         nomeMedicamento[21], 
         tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO], 
         instrucoes[MAX_TAM_INSTRUCOES], motivo[300], 
         especialidade[50];
    int opcao = 0, qtd = 0;
    eTipoUso tipoUso;
    while (1) {
        ImprimeMenuConsulta();
        scanf("%d%*c", &opcao);
        switch (opcao) {
            case CADASTRAR_LESAO:
                printf("#################### CONSULTA MEDICA #######################\n");
                LeLesaoConsulta(consulta);
                printf("\nLESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case GERAR_RECEITA_MEDICA:
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("RECEITA MEDICA:\n");
                printf("TIPO DE USO: ");                        scanf("%[^\n]%*c", tipo);
                printf("NOME DO MEDICAMENTO: ");                scanf("%[^\n]%*c", nomeMedicamento);
                printf("TIPO DE MEDICAMENTO: ");                scanf("%[^\n]%*c", tipoMedicamento);
                printf("QUANTIDADE: ");                         scanf("%d%*c", &qtd);
                printf("INSTRUCOES DE USO: ");                  scanf("%[^\n]%*c", instrucoes);

                if (strcmp(tipo, "ORAL")) tipoUso = ORAL;
                else if (strcmp(tipo, "TOPICO")) tipoUso = TOPICO;

                insereDocumentoFila(fila, criaReceita(ObtemNomePessoa(consulta->paciente), tipoUso, nomeMedicamento, tipoMedicamento, 
                                    instrucoes, qtd, ObtemNomeMedico(consulta->medico), ObtemCRM(consulta->medico), ObtemDataString(consulta->dataConsulta)), 
                                    imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                printf("\nRECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case SOLICITACAO_DE_BIOPSIA:
                printf("#################### CONSULTA MEDICA #######################\n");
                insereDocumentoFila(fila, CriaBiopsia(ObtemNomePessoa(consulta->paciente), ObtemCPFPessoa(consulta->paciente), 
                                    consulta->lesao, consulta->qtdLesoes, ObtemNomeMedico(consulta->medico), ObtemCRM(consulta->medico), 
                                    ObtemDataString(consulta->dataConsulta)), ImprimeBiopsiaTela, ImprimeBiopsiaArquivo, DesalocaBiopsia);
                
                printf("\nSOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case ENCAMINHAMENTO:
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("ENCAMINHAMENTO:\n");
                printf("ESPECIALIDADE ENCAMINHADA: ");          scanf("%[^\n]%*c", especialidade);
                printf("MOTIVO: ");                             scanf("%[^\n]%*c", motivo);
                insereDocumentoFila(fila, CriaEncaminhamento(ObtemNomePessoa(consulta->paciente), ObtemCPFPessoa(consulta->paciente), 
                                    especialidade, motivo, ObtemNomeMedico(consulta->medico), ObtemCRM(consulta->medico), 
                                    ObtemDataString(consulta->dataConsulta)), ImprimeEncaminhamentoTela, ImprimeEncaminhamentoArquivo, 
                                    DesalocaEncaminhamento);

                printf("\nENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
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
    printf("TAMANHO: ");                            scanf("%d%*c", &tamanho);
    printf("ENVIAR PARA CIRURGIA: ");               scanf("%d%*c", &cirurgia);
    printf("ENVIAR PARA A CRIOTERAPIA: ");          scanf("%d%*c", &crioterapia);
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