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
    char tipoPele[3];
};

tConsulta * CriaConsulta (tPessoa * pessoa, tMedico * medico) {
    
    tConsulta * consulta = calloc(1, sizeof(tConsulta));
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

    // if (consulta->paciente) DesalocaPessoa(consulta->paciente);
    // if (consulta->medico) DesalocaMedico(consulta->medico);
    if (consulta->dataConsulta != NULL) {
        DesalocaData(consulta->dataConsulta);
    }

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

    char nomePaciente[100], cpfPaciente[15], nomeMedico[100], crmMedico[12], stringDataConsulta[10];
    strcpy(nomePaciente, ObtemNomePessoa(consulta->paciente));
    strcpy(cpfPaciente, ObtemCPFPessoa(consulta->paciente));

    if (consulta->medico) strcpy(nomeMedico, ObtemNomeMedico(consulta->medico));
    else nomeMedico[0] = '\0';

    if (consulta->medico) strcpy(crmMedico, ObtemCRM(consulta->medico));
    else crmMedico[0] = '\0';

    strcpy(stringDataConsulta, ObtemDataString(consulta->dataConsulta));

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
                printf("TIPO DE USO: ");                        scanf("%s%*c", tipo);
                printf("NOME DO MEDICAMENTO: ");                scanf("%[^\n]%*c", nomeMedicamento);
                printf("TIPO DE MEDICAMENTO: ");                scanf("%[^\n]%*c", tipoMedicamento);
                printf("QUANTIDADE: ");                         scanf("%d%*c", &qtd);
                printf("INSTRUCOES DE USO: ");                  scanf("%[^\n]%*c", instrucoes);

                if (strcmp(tipo, "ORAL") == 0) 
                    tipoUso = ORAL;

                else if (strcmp(tipo, "TOPICO") == 0)
                    tipoUso = TOPICO;

                tReceita * r = criaReceita(nomePaciente, tipoUso, nomeMedicamento, 
                                    tipoMedicamento, instrucoes, qtd, nomeMedico, crmMedico, 
                                    stringDataConsulta);

                insereDocumentoFila(fila, r, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                printf("\nRECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case SOLICITACAO_DE_BIOPSIA:
                printf("#################### CONSULTA MEDICA #######################\n");
                tBiopsia * b = CriaBiopsia(nomePaciente, cpfPaciente, 
                                    consulta->lesao, consulta->qtdLesoes, nomeMedico, crmMedico, 
                                    stringDataConsulta);
                insereDocumentoFila(fila,b , ImprimeBiopsiaTela, ImprimeBiopsiaArquivo, DesalocaBiopsia);
                
                consulta->biopsia = b;
                printf("\nSOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case ENCAMINHAMENTO:
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("ENCAMINHAMENTO:\n");
                printf("ESPECIALIDADE ENCAMINHADA: ");          scanf("%[^\n]%*c", especialidade);
                printf("MOTIVO: ");                             scanf("%[^\n]%*c", motivo);

                tEncaminhamento * e = CriaEncaminhamento(nomePaciente, cpfPaciente, 
                                    especialidade, motivo, nomeMedico, crmMedico, 
                                    stringDataConsulta);
                insereDocumentoFila(fila, e, ImprimeEncaminhamentoTela, ImprimeEncaminhamentoArquivo, 
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
    consulta->lesao[consulta->qtdLesoes-1] = CriaLesao(consulta->qtdLesoes, diagonostico, regiao, tamanho, cirurgia, crioterapia);
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

int RetornaQtdLesoesConsulta (tConsulta * consulta) {
    if (!consulta) return 0;
    return consulta->qtdLesoes;
}

int RetornaQtdReceitasConsulta (tConsulta * consulta) {
    if (!consulta) return 0;
    return consulta->qtdReceitas;
}

int RetornaQtdEncaminhamentosConsulta (tConsulta * consulta) {
    if (!consulta) return 0;
    return consulta->qtdEncaminhamentos;
}

int RetornaPrecisaDeCirurgiaConsulta (tConsulta * consulta) {
    int cont = 0;
    if (!consulta) return 0;
    for (int i = 0; i < consulta->qtdLesoes; i++) 
        cont += NecessitaCirurgia(consulta->lesao[i]);

    return cont;
}


int RetornaPrecisaDeCrioterapiaConsulrta (tConsulta * consulta) {
     int cont = 0;
    if (!consulta) return 0;
    for (int i = 0; i < consulta->qtdLesoes; i++) 
        cont += NecessitaCrioterapia(consulta->lesao[i]);

    return cont;
}

int RetornaTamanhoLesaoConsulta (tConsulta * consulta, int indice) {
    if (!consulta) return 0;
    return ObtemTamanhoLesao(consulta->lesao[indice]);
}