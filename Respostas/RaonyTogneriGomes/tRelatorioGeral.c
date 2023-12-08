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

tRelatorioGeral * CriaRelatorioGeral (tPessoa ** pessoas, int qtdPessoas, 
                                      tLesao ** lesoes, int qtdLesoes, int qtdConsultas) {
    tRelatorioGeral * relatorio = malloc(sizeof(tRelatorioGeral));
    relatorio->pacientesAtendidos = qtdConsultas;
    relatorio->idadeMedia = CalculaMediaIdade(pessoas, qtdPessoas);
    relatorio->qtdFem = RetornaQtdMulheres(pessoas, qtdPessoas);
    relatorio->qtdMasc = RetornaQtdHomens(pessoas, qtdPessoas);
    relatorio->qtdOutro = RetornaQtdOutros(pessoas, qtdPessoas);
    relatorio->tamMedioLesao = TamanhoMedioLesoes(lesoes, qtdLesoes);
    relatorio->qtdLesoes = qtdLesoes;
    relatorio->qtdCirurgias = RetornaQtdCirurgias(lesoes, qtdLesoes);
    relatorio->qtdCrioterapias = RetornaQtdCrioterapia(lesoes, qtdLesoes);
    return relatorio;
}


void ExecutaRelatorioGeral (tFila * fila, tPessoa ** pessoas, int qtdPessoas, tLesao ** lesoes, 
                            int qtdLesoes, int qtdConsultas, char * pathSaida) {
    int opcaoMenu = 0;
    while (1) {
        ImprimeMenuFilaImpressao();
        scanf("%d", &opcaoMenu);
        switch (opcaoMenu) {
            case 1:
                insereDocumentoFila(fila, CriaRelatorioGeral(pessoas, qtdPessoas, lesoes, qtdLesoes, qtdConsultas), 
                                    ImprimeRelatorioGeralTela, ImprimeRelatorioGeralArquivo, DesalocaRelatorioGeral);

                imprimeFila(fila, pathSaida);

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

int CalculaMediaIdade (tPessoa ** pessoas, int qtdPessoas) {
    if (qtdPessoas == 0) return 0;
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        cont += CalculaIdade(ObtemDataPessoa(pessoas[i]));
    }
    return cont/qtdPessoas;
}

int RetornaQtdMulheres (tPessoa ** pessoas, int qtdPessoas) {
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (strcmp(ObtemGeneroPessoa(pessoas[i]), "FEMININO") == 0) cont++;
    }
    return cont;
}

int RetornaQtdHomens (tPessoa ** pessoas, int qtdPessoas) {
        int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (strcmp(ObtemGeneroPessoa(pessoas[i]), "MASCULINO") == 0) cont++;
    }
    return cont;
}

int RetornaQtdOutros (tPessoa ** pessoas, int qtdPessoas) {
    int cont = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (strcmp(ObtemGeneroPessoa(pessoas[i]), "OUTROS") == 0) cont++;
    }
    return cont;
}

int TamanhoMedioLesoes (tLesao ** lesoes, int qtdLesoes) {
    if (qtdLesoes == 0) return 0;
    int cont = 0;
    for (int i = 0; i < qtdLesoes; i++) {
        cont += ObtemTamanhoLesao(lesoes[i]);
    }

    return cont/qtdLesoes;
}

int RetornaQtdCirurgias (tLesao ** lesoes, int qtdLesoes) {
    int cont = 0;
    for (int i = 0; i < qtdLesoes; i++) {
        if (NecessitaCirurgia(lesoes[i])) cont++;
    }
    return cont;
}

int RetornaQtdCrioterapia (tLesao ** lesoes, int qtdLesoes) {
    int cont = 0;
    for (int i = 0; i < qtdLesoes; i++) {
        if (NecessitaCrioterapia(lesoes[i])) cont++;
    }
    return cont;
}