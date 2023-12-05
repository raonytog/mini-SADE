#include "tFila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tFila {
    tDocumento ** documentos;
    int qtdDoc;
};

tFila *criaFila() {
    tFila * fila = malloc(sizeof(tFila));
    fila->documentos = NULL;
    fila->qtdDoc = 0;
    return fila;
}

void desalocaFila(tFila *f) {
    if (!f) return;
    for (int i = 0; i < f->qtdDoc; i++)
        desalocaDocumento(f->documentos[i]);

    free(f->documentos);
    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                         func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                         func_ptr_desaloca desaloca) {
    if (!f) return;
    f->qtdDoc++;
    f->documentos = realloc(f->documentos, f->qtdDoc * sizeof(tDocumento *));
    f->documentos[f->qtdDoc-1] = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);;
}

int quantidadeDocumentosNaFila(tFila *f) {
    if (!f) return 0;
    return f->qtdDoc;
}

void imprimeFila(tFila *f, char *path) {
    if (!f) return;
    for (int i = 0; i < f->qtdDoc; i++) {
        imprimeNaTelaDocumento(f->documentos[i]);
        imprimeEmArquivoDocumento(f->documentos[i], path);
    }
}