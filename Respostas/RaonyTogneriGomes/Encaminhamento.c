#include "Encaminhamento.h"
#include <stdio.h>

void ImprimeEncaminhamentoTela (tPessoa * paciente, char * especialidade, char * motivo, 
                                tMedico * medico, char * data) {
    printf("PACIENTE: %s\n", (ObtemNomePessoa(paciente)));
    printf("CPF: %s\n\n", ObtemCPFPessoa(paciente));

    printf("ESPECIALIDADE ENCAMINHADA: %s\n", especialidade);
    printf("MOTIVO: %s\n\n", motivo);

    printf("%s (%s)\n", ObtemNomeMedico(medico), ObtemCRM(medico));
    printf("%s\n\n", data);
}

void ImprimeEncaminhamentoArquivo (tPessoa * paciente, char * especialidade, char * motivo, 
                                tMedico * medico, char * data, char * path) {
    
    char diretorio[1001];
    sprintf(diretorio, "%s/encaminhamento.txt", path);
    FILE * fEncaminhamento = NULL;
    fEncaminhamento = fopen(diretorio, "a+b");

    sprintf(fEncaminhamento, "PACIENTE: %s\n", (ObtemNomePessoa(paciente)));
    sprintf(fEncaminhamento, "CPF: %s\n\n", ObtemCPFPessoa(paciente));

    sprintf(fEncaminhamento, "ESPECIALIDADE ENCAMINHADA: %s\n", especialidade);
    sprintf(fEncaminhamento, "MOTIVO: %s\n\n", motivo);

    sprintf(fEncaminhamento, "%s (%s)\n", ObtemNomeMedico(medico), ObtemCRM(medico));
    sprintf(fEncaminhamento, "%s\n\n", data);
    
    fclose(fEncaminhamento);
}
