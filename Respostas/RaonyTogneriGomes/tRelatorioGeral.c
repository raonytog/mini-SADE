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
    tRelatorioGeral * relatorio = malloc(sizeof(tRelatorioGeral));
    relatorio->pacientesAtendidos = qtdConsultas;
    relatorio->idadeMedia = CalculaMediaIdade(pessoas, qtdPessoas);
    relatorio->qtdFem = RetornaQtdMulheres(pessoas, qtdPessoas);
    relatorio->qtdMasc = RetornaQtdHomens(pessoas, qtdPessoas);
    relatorio->qtdOutro = RetornaQtdOutros(pessoas, qtdPessoas);
    relatorio->tamMedioLesao = TamanhoMedioLesoes(consultas, qtdConsultas);
    relatorio->qtdLesoes = RetornaQtdLesoes(consultas, qtdConsultas);
    relatorio->qtdCirurgias = RetornaQtdCirurgias(consultas, qtdConsultas);
    relatorio->qtdCrioterapias = RetornaQtdCrioterapia(consultas, qtdConsultas);
    return relatorio;
}


void ExecutaRelatorioGeral (tFila * fila, tPessoa ** pessoas, int qtdPessoas, tConsulta ** consultas, 
                            int qtdConsultas, char * pathSaida) {
    int opcaoMenu = 0;
    while (1) {
        ImprimeMenuFilaImpressao();
        scanf("%d", &opcaoMenu);
        switch (opcaoMenu) {
            case 1:
                tRelatorioGeral * relatorio = CriaRelatorioGeral(pessoas, qtdPessoas, consultas, qtdConsultas);
                insereDocumentoFila(fila, relatorio, ImprimeRelatorioGeralTela, 
                                    ImprimeRelatorioGeralArquivo, DesalocaRelatorioGeral);

            case 2:
                return;
                break;
        }
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
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n",relatorio->qtdCrioterapias);
}

void ImprimeRelatorioGeralArquivo (void * data, char * path) {
    tRelatorioGeral * relatorio = (tRelatorioGeral *) data;

    FILE * fRelatorio = NULL;
    fRelatorio = fopen(path, "a");
    if (!fRelatorio) {
        printf("fRelatorio nao abriu\n");
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
    fprintf(fRelatorio, "NUMERO TOTAL DE CRIOTERAPIA: %d\n",relatorio->qtdCrioterapias);

    fclose(fRelatorio);
}


void DesalocaRelatorioGeral (void * data) {
    tRelatorioGeral * relatorio = (tRelatorioGeral *) data;
    free(relatorio);
}

int CalculaMediaIdadeRelatorioGeral (tPessoa ** pessoas, int qtdPessoas) {
    if (qtdPessoas == 0) return 0;
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        cont += CalculaIdade(ObtemDataPessoa(pessoas[i]));
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

int TamanhoMedioLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0, qtd = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        for (int j = 0; j < RetornaQtdLesoesConsulta(consultas[i]); j++) {
            cont += RetornaQtdLesoesConsulta(consultas[i]);
            qtd++;
        }
    }
    if (qtd != 0) return cont/qtd;
    return 0;
}

int RetornaQtdCirurgiasRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0, qtd = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        cont += RetornaPrecisaDeCirurgiaConsulta(consultas[i]);
    }
    if (qtd != 0) return cont/qtd;
    return 0;
}

int RetornaQtdCrioterapiaRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0, qtd = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        cont += RetornaPrecisaDeCrioterapiaConsulrta(consultas[i]);
    }
    if (qtd != 0) return cont/qtd;
    return 0;
}

int RetornaQtdLesoesRelatorioGeral (tConsulta ** consultas, int qtdConsultas) {
    int cont = 0, qtd = 0;
    for (int i = 0; i < qtdConsultas; i++) {
        for (int j = 0; j < RetornaQtdLesoesConsulta(consultas[i]); j++) {
            qtd++;
        }
    }

    return qtd;
}