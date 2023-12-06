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

    int qtdLesoes;
    tLesao ** lesao;
    tReceita * receita;
    tBiopsia * biopsia;
    tEncaminhamento * encaminhamento;
    
    int diabetico, fumante, alergico, historicoCancerigeno;
    char tipoPele[2];
};

tConsulta * CriaConsulta (tPessoa * pessoa, tMedico * medico) {
    
    tConsulta * consulta = malloc(sizeof(tConsulta));
    if (!consulta) return NULL;
 
    consulta->paciente = pessoa;
    consulta->medico = medico;

    tData * dataConsulta = LeDataConsulta();
    printf("POSSUI DIABETES: ");                    scanf("%d",  &consulta->diabetico);
    printf("FUMANTE: ");                            scanf("%d",  &consulta->fumante);
    printf("ALERGIA A MEDICAMENTO: ");              scanf("%d",  &consulta->alergico);
    printf("HISTORICO DE CANCER: ");                scanf("%d",  &consulta->historicoCancerigeno);
    printf("TIPO DE PELE: ");                       scanf("%[^\n]%*c",  consulta->tipoPele);

    return dataConsulta;
}

void DesalocaConsulta (tConsulta * consulta);

bool EstaCadastradoPacienteCpf (tListaPessoas * lista, char * cpf) {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: %s\n", cpf);
    int tam = ObtemNumeroPessoasLista(lista);

    for (int i = 0; i < tam; i++) {
        tPessoa * p = ObtemPessoaIndice(lista, i);
        if (strcmp( ObtemCPFPessoa(p), cpf ) == 0) {
            printf("---\n");
            printf("-NOME: %s", ObtemNomePessoa(p));
            ImprimeData( ObtemDataPessoa(p) );
            printf("---\n");
            return true;
        }
    }
    printf("PACIENTE SEM CADASTRO\n");
    printf("############################################################");
    return false;

}

void ImprimeMenuConsulta () {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO: ");
	printf("\t(1) CADASTRAR LESAO\n");
	printf("\t(2) GERAR RECEITA MEDICA\n");
	printf("\t(3) SOLICITACAO DE BIOPSIA\n");
	printf("\t(4) ENCAMINHAMENTO\n");
	printf("\t(5) ENCERRAR CONSULTA\n");
    printf("############################################################");
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

    tReceita * receita = criaReceita( ObtemNomePessoa(consulta), tipo, nomeMedicamento, tipoMedicamento, 
                 instrucoes, qtdMedicamento, ObtemNomeMedico(consulta->medico), 
                 ObtemCRM(consulta->medico), ObtemDataString(consulta->dataConsulta));

    consulta->receita = receita;

    tDocumento * doc = criaDocumento(consulta->receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    insereDocumentoFila(fila, doc, imprimeNaTelaDocumento, imprimeEmArquivoDocumento, desalocaDocumento);
    
}

void LeLesaoConsulta (tConsulta * consulta, tFila * fila) {
    char diagonostico[20], regiao[20];
    int tamanho, cirurgia, crioterapia;
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");
    printf("DIAGONISTICO CLINICO: ");               scanf("%[^\n]%*c", diagonostico);
    printf("REGIAO DO CORPO: ");                    scanf("%[^\n]%*c", regiao);
    printf("TAMANHO: ");                            scanf("%d", tamanho);
    printf("ENVIAR PARA CIRURGIA: ");               scanf("%d", cirurgia);
    printf("ENVIAR PARA A CRIOTERAPIA: ");          scanf("%d", crioterapia);
    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c");

    (consulta->qtdLesoes)++;
    tLesao * lesao = CriaLesao(consulta->qtdLesoes, diagonostico, regiao, tamanho);
}

void LeBiopsiaConsulta (tConsulta * consulta, tFila * fila);

void LeEncaminhamentoConsulta (tConsulta * consulta, tFila * fila);