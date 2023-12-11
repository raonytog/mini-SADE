#include "tConsulta.h"
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
    char nomePaciente[100];
    char cpf[15];

    char nomeMedico[100];
    char crm[15];

    int dia, mes, ano;
    char data[20];

    tLesao ** lesao;
    int qtdLesoes;
    
    int diabetico, fumante, alergico, historicoCancerigeno;
    char tipoPele[3];
};

tConsulta * CriaConsulta (tPessoa * pessoa, tMedico * medico) {
    
    AtualizaPessoaComoAtendida(pessoa);
    tConsulta * consulta = calloc(1, sizeof(tConsulta));
    if (!consulta) return NULL;
    strcpy(consulta->nomePaciente, ObtemNomePessoa(pessoa));
    strcpy(consulta->cpf, ObtemCPFPessoa(pessoa));

    if (!medico) {
        strcpy(consulta->nomeMedico, ObtemNomeMedico(medico));
        strcpy(consulta->crm, ObtemCRM(medico));

    } else {
        consulta->nomeMedico[0] = '\0';
        consulta->crm[0] = '\0';
    }

    consulta->lesao = NULL;
    consulta->qtdLesoes = 0;

    printf("DATA DA CONSULTA: ");                   scanf("%d/%d/%d", &consulta->dia, &consulta->mes, &consulta->ano);
    printf("POSSUI DIABETES: ");                    scanf("%d%*c",  &consulta->diabetico);
    printf("FUMANTE: ");                            scanf("%d%*c",  &consulta->fumante);
    printf("ALERGIA A MEDICAMENTO: ");              scanf("%d%*c",  &consulta->alergico);
    printf("HISTORICO DE CANCER: ");                scanf("%d%*c",  &consulta->historicoCancerigeno);
    printf("TIPO DE PELE: ");                       scanf("%[^\n]%*c",  consulta->tipoPele);
    printf("\n############################################################\n");

    sprintf(consulta->data, "%d/%d/%d", consulta->dia, consulta->mes, consulta->ano);
    return consulta;
}

void DesalocaConsulta (tConsulta * consulta) {
    if (!consulta) return;

    for (int i = 0; i < consulta->qtdLesoes; i++) {
        DesalocaLesao(consulta->lesao[i]);
        consulta->lesao[i] = NULL;
    }
    free(consulta->lesao);
    consulta->lesao = NULL;

    free(consulta);
    consulta = NULL;
}

void ExecutaConsulta (tConsulta * consulta, tFila * fila, int EhMedico) {
    char tipo[7], 
         nomeMedicamento[21], 
         tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO], 
         instrucoes[MAX_TAM_INSTRUCOES], motivo[300], 
         especialidade[50],
         vazio[10];

    // char nomePaciente[100], cpfPaciente[15], nomeMedico[100], crmMedico[12], stringDataConsulta[10];
    // strcpy(nomePaciente, ObtemNomePessoa(consulta->paciente));
    // strcpy(cpfPaciente, ObtemCPFPessoa(consulta->paciente));

    // if (consulta->medico) strcpy(nomeMedico, ObtemNomeMedico(consulta->medico));
    // else nomeMedico[0] = '\0';

    // if (consulta->medico) strcpy(crmMedico, ObtemCRM(consulta->medico));
    // else crmMedico[0] = '\0';

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

                tReceita * r;
                r = criaReceita(consulta->nomePaciente, tipoUso, nomeMedicamento, tipoMedicamento, 
                    instrucoes, qtd, consulta->nomeMedico, consulta->crm, consulta->data);


                insereDocumentoFila(fila, r, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                printf("\nRECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case SOLICITACAO_DE_BIOPSIA:
                printf("#################### CONSULTA MEDICA #######################\n");
                tBiopsia * b = CriaBiopsia(consulta->nomePaciente, consulta->cpf, consulta->lesao, 
                            consulta->qtdLesoes, consulta->nomeMedico, consulta->crm, consulta->data);
                insereDocumentoFila(fila,b , ImprimeBiopsiaTela, ImprimeBiopsiaArquivo, DesalocaBiopsia);
                
                printf("\nSOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c");
                break;

            case ENCAMINHAMENTO:
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("ENCAMINHAMENTO:\n");
                printf("ESPECIALIDADE ENCAMINHADA: ");          scanf("%[^\n]%*c", especialidade);
                printf("MOTIVO: ");                             scanf("%[^\n]%*c", motivo);

                tEncaminhamento * e = CriaEncaminhamento(consulta->nomePaciente, consulta->cpf, especialidade, motivo, 
                                consulta->nomeMedico, consulta->crm, consulta->data);

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

int RetornaQtdLesoesConsulta (tConsulta * consulta) {
    if (!consulta) return 0;
    return consulta->qtdLesoes;
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

void SalvaConsulta (tConsulta * consulta, FILE * arquivo) {
    fwrite(consulta, sizeof(tConsulta), 1, arquivo);
}

tConsulta ** RecuperaConsulta (FILE * arquivo, int * qtdConsultas) {
    fread(qtdConsultas, sizeof(int), 1, arquivo);
    tConsulta ** consulta = (tConsulta **) calloc(*qtdConsultas, sizeof(tConsulta *));
    if (!consulta) {
        printf("Erro ao alocar memória para recuperar consulta\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *qtdConsultas; i++) {
        consulta[i] = calloc (1, sizeof(tConsulta));
        fread(consulta[i], sizeof(tConsulta), 1, arquivo);
        
        consulta[i]->lesao = calloc(consulta[i]->qtdLesoes, sizeof(tLesao *));
        for (int j = 0; j < consulta[i]->qtdLesoes; j++) {
            consulta[i]->lesao[j] = RecuperaLesao(arquivo);
        }
    }

    return consulta;
}

void SalvaConsultaBinario (tConsulta ** consultas, int qtdConsultas, char * path) {
    char dir[1001];
    sprintf(dir, "%s/consultas.bin", path);
    FILE * arquivo = fopen(dir, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar\n");
        exit(EXIT_FAILURE);
    }
    
    fwrite(&qtdConsultas, sizeof(int), 1, arquivo);
    for (int i = 0; i < qtdConsultas; i++) {
        fwrite(consultas[i], sizeof(tConsulta), 1, arquivo);
        for (int j = 0; j < consultas[i]->qtdLesoes; j++)
            SalvaLesao(consultas[i]->lesao[j], arquivo);
    }

    fclose(arquivo);
}

