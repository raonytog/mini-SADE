#include "tRelatorioGeral.h"
#include "tMenu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tRelatorioGeral {
    int pacientesAtendidos;
    int idadeMedia;
    int qtdFem;
    int qtdMasc;
    int qtdOutro;
    int tamMedioLesao;
    int qtdLesoes;
    int qtdCirurgias;
    int qtdCrioterapias;
};

tRelatorioGeral * CriaRelatorioGeral (tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, int qtdConsultas) {
    tRelatorioGeral * relatorio = calloc(1, sizeof(tRelatorioGeral));
    relatorio->pacientesAtendidos = RetornaQtdPessoasAtentidas(pessoas, qtdPessoas);
    relatorio->idadeMedia = CalculaMediaIdadeRelatorioGeral(pessoas, qtdPessoas);
    relatorio->qtdFem = RetornaQtdMulheresRelatorioGeral(pessoas, qtdPessoas);
    relatorio->qtdMasc = RetornaQtdHomensRelatorioGeral(pessoas, qtdPessoas);
    relatorio->qtdOutro = RetornaQtdOutrosRelatorioGeral(pessoas, qtdPessoas);
    relatorio->tamMedioLesao = TamanhoMedioLesoesRelatorioGeral(consultas, qtdConsultas);
    relatorio->qtdLesoes = RetornaQtdLesoesRelatorioGeral(consultas, qtdConsultas);
    relatorio->qtdCirurgias = RetornaQtdCirurgiasRelatorioGeral(consultas, qtdConsultas);
    relatorio->qtdCrioterapias = RetornaQtdCrioterapiaRelatorioGeral(consultas, qtdConsultas);
    return relatorio;
}


void ExecutaRelatorioGeral (tFila * fila, tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, 
                            int qtdConsultas, char * pathSaida) {
    int opcaoMenu = 0;
    tRelatorioGeral * relatorio = CriaRelatorioGeral(pessoas, qtdPessoas, consultas, qtdConsultas);
    printf("#################### RELATORIO GERAL #######################\n");
    ImprimeRelatorioGeralTela(relatorio);

    ImprimeMenuRelatorio();
    scanf("%d%*c", &opcaoMenu);
    switch (opcaoMenu) {
        case 1:
            insereDocumentoFila(fila, relatorio, ImprimeRelatorioGeralTela, 
                                ImprimeRelatorioGeralArquivo, DesalocaRelatorioGeral);
            printf("RELATORIO ENVIADO PARA FILA DE IMPRESSAO. PRESIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
            printf("############################################################\n");
            scanf("%*c");
            return;
                
        case 2:
            return;
            break;
    }
}

void ImprimeRelatorioGeralTela (void * data) {
    tRelatorioGeral * relatorio = (tRelatorioGeral *) data;
    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", relatorio->pacientesAtendidos);
    printf("IDADE MEDIA: %d\n", relatorio->idadeMedia);
    printf("DISTRIBUICAO POR GENERO:\n");
    printf("- FEMININO: %d\n", relatorio->qtdFem);
    printf("- MASCULINO: %d\n", relatorio->qtdMasc);
    printf("- OUTROS: %d\n", relatorio->qtdOutro);
    printf("TAMANHO MEDIO DAS LESOES: %d\n", relatorio->tamMedioLesao);
    printf("NUMERO TOTAL DE LESOES: %d\n", relatorio->qtdLesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d\n", relatorio->qtdCirurgias);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n\n",relatorio->qtdCrioterapias);
}

void ImprimeRelatorioGeralArquivo (void * data, char * path) {
    char diretorio[1001];
    sprintf(diretorio, "%s/relatorio_geral.txt", path);

    tRelatorioGeral * relatorio = (tRelatorioGeral *) data;
    FILE * fRelatorio = NULL;
    fRelatorio = fopen(diretorio, "a");
    if (!fRelatorio) {
        printf("fRelatorio nao abriu\n");
        return;
    }

    fprintf(fRelatorio, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", relatorio->pacientesAtendidos);
    fprintf(fRelatorio, "IDADE MEDIA: %d\n", relatorio->idadeMedia);
    fprintf(fRelatorio, "DISTRIBUICAO POR GENERO:\n");
    fprintf(fRelatorio, "- FEMININO: %d\n", relatorio->qtdFem);
    fprintf(fRelatorio, "- MASCULINO: %d\n", relatorio->qtdMasc);
    fprintf(fRelatorio, "- OUTROS: %d\n", relatorio->qtdOutro);
    fprintf(fRelatorio, "TAMANHO MEDIO DAS LESOES: %d\n", relatorio->tamMedioLesao);
    fprintf(fRelatorio, "NUMERO TOTAL DE LESOES: %d\n", relatorio->qtdLesoes);
    fprintf(fRelatorio, "NUMERO TOTAL DE CIRURGIAS: %d\n", relatorio->qtdCirurgias);
    fprintf(fRelatorio, "NUMERO TOTAL DE CRIOTERAPIA: %d\n\n",relatorio->qtdCrioterapias);

    fclose(fRelatorio);
}


void DesalocaRelatorioGeral (void * data) {
    tRelatorioGeral * relatorio = (tRelatorioGeral *) data;
    if (!relatorio) return;
    free(relatorio);
    relatorio = NULL;
}

int CalculaMediaIdadeRelatorioGeral (tPessoa ** pessoas, int qtdPessoas) {
    if (qtdPessoas == 0) return 0;
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        cont += CalculaIdade(pessoas[i]);
    }
    return cont/qtdPessoas;
}

int RetornaQtdMulheresRelatorioGeral (tPessoa ** pessoas, int qtdPessoas) {
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (strcmp(ObtemGeneroPessoa(pessoas[i]), "FEMININO") == 0) cont++;
    }
    return cont;
}

int RetornaQtdHomensRelatorioGeral (tPessoa ** pessoas, int qtdPessoas) {
        int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (strcmp(ObtemGeneroPessoa(pessoas[i]), "MASCULINO") == 0) cont++;
    }
    return cont;
}

int RetornaQtdOutrosRelatorioGeral (tPessoa ** pessoas, int qtdPessoas) {
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (strcmp(ObtemGeneroPessoa(pessoas[i]), "OUTROS") == 0) cont++;
    }
    return cont;
}

int RetornaQtdPessoasAtentidas (tPessoa ** pessoas, int qtdPessoas) {
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (ObtemSeFoiAtendido(pessoas[i])) cont++;
    }
    return cont;
}

int TamanhoMedioLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0, qtd = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        for (int j = 0; j < RetornaQtdLesoesConsulta(consultas[i]); j++) {
            cont += RetornaTamanhoLesaoConsulta(consultas[i], j);
            qtd++;
        }
    }
    if (qtd != 0) return cont/qtd;
    return 0;
}

int RetornaQtdCirurgiasRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        cont += RetornaPrecisaDeCirurgiaConsulta(consultas[i]);
    }
    return cont;
}

int RetornaQtdCrioterapiaRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        cont += RetornaPrecisaDeCrioterapiaConsulrta(consultas[i]);
    }
    return cont;
}

int RetornaQtdLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int qtd = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        for (int j = 0; j < RetornaQtdLesoesConsulta(consultas[i]); j++) {
            qtd++;
        }
    }

    return qtd;
}

int CalculaIdade(tPessoa * pessoa) {
    int dia = ObtemDiaPessoa(pessoa),
        mes = ObtemMesPessoa(pessoa), 
        ano = ObtemAnoPessoa(pessoa),
        idade = 2023 - ano;

    if (mes > 11 || (mes == 11 && dia >= 9)) idade++; 
    return idade;
}