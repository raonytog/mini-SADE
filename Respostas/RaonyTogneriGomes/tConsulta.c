#include "tConsulta.h"
#include "tData.h"
#include "tPessoa.h"
#include "tMedico.h"

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

    tLesao * lesao;
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

void LeReceitaConsulta(tConsulta * consulta);