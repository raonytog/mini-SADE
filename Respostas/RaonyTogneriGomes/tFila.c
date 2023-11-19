#include "tFila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tFila {
    int qtdDoc;
    tDocumento **documentos;
};

tFila *criaFila() {
    tFila * fila = malloc(sizeof(tFila));
    fila->documentos = NULL;
    fila->qtdDoc = 0;
    return fila;
}

void desalocaFila(tFila *f) {
    for (int i = 0; i < f->qtdDoc; i++)
        free(f->documentos[i]);
    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                         func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                         func_ptr_desaloca desaloca) {
    int tamFila = quantidadeDocumentosNaFila(f);
    tDocumento * doc = criaDocumento(dado, imprimeNaTela, imprimeEmArquivoDocumento, desaloca);
    
    f->documentos[tamFila] = doc;
    (f->qtdDoc)++;
}

int quantidadeDocumentosNaFila(tFila *f) {
    return f->qtdDoc;
}

void imprimeFila(tFila *f, char *path) {
    for (int i = 0; i < quantidadeDocumentosNaFila(f); i++) {
        imprimeNaTelaDocumento(f->documentos[i]);
        imprimeEmArquivoDocumento(f->documentos[i], path);
    }
}