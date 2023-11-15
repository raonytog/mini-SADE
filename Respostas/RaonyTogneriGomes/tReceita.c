#include "tReceita.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tReceita {
    eTipoUso tipoUso;
    char * nomePaciente;
    char * nomeMedicamento;
    char * tipoMedicamento;
    char * instrucoes;
    char * nomeMedico;
    char * CRM;
    char * dataString;
    int qtd;
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr) {
    tReceita * receita = malloc (sizeof(tReceita));

    receita->tipoUso = tipoUso;
    receita->qtd = qntd;

    receita->nomePaciente = malloc(strlen(nomePaciente)+1 * sizeof(char));
    strcpy(receita->nomePaciente, nomePaciente);

    receita->nomeMedicamento = malloc(strlen(nomeMedicamento)+1 * sizeof(char));
    strcpy(receita->nomeMedicamento, nomeMedicamento);

    receita->tipoMedicamento = malloc(stren(tipoMedicamento)+1 * sizeof(char));
    strcpy(receita->tipoMedicamento, tipoMedicamento);

    receita->instrucoes = malloc(strlen(instrucoes)+1 * sizeof(char));
    strcpy(receita->instrucoes, instrucoes);

    receita->nomeMedicamento = malloc(strlen(nomeMedico)+1 * sizeof(char));
    strcpy(receita->nomeMedico, nomeMedico);

    receita->CRM = malloc(strlen(CRM)+1 * sizeof(char));
    strcpy(receita->CRM, CRM);

    receita->dataString = malloc(strlen(dataStr)+1 * sizeof(char));
    strcpy(receita->dataString, dataStr);

    return receita;
}


void desalocaReceita(void *dado) {
    if (dado == NULL) return;

    tReceita * receita = (tReceita*) dado;
    free(receita->CRM);
    free(receita->dataString);
    free(receita->instrucoes);
    free(receita->nomeMedicamento);
    free(receita->nomeMedico);
    free(receita->nomePaciente);
    free(receita->tipoMedicamento);
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma receita) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaReceita(void *dado) {
    tReceita *receita = (tReceita*)dado;

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("RECEITA MEDICA:\n");
    printf("TIPO DE USO: %s\n", receita->tipoUso);
    printf("NOME DO MEDICAMENTO: %s\n", receita->nomeMedicamento);
    printf("QUANTIDADE: %d\n", receita->qtd);
    printf("INSTRUÇÕES DE USO: %s\n", receita->instrucoes);
    printf("\n");
    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma receita) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoReceita(void *dado, char *path) {
    FILE * fReceita = NULL;

    char diretorio[1001];
    sprintf(diretorio, "%s/NOME_ARQUIVO_RECEITA", path);

    fopen(diretorio, "w");
    // tem q printar mas eu nem sei direito oq 
    fclose(diretorio);
}
