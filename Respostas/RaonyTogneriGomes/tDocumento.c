#include "tDocumento.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tDocumento {
    void *dado;
    func_ptr_imprimeNaTela imprimeNaTela;
    func_ptr_imprimeEmArquivo ImprimeEmArquivo;
    func_ptr_desaloca desaloca;
};

tDocumento *criaDocumento(void *dado, 
                          func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                          func_ptr_desaloca desaloca) {

        
    tDocumento * documento = malloc (sizeof(tDocumento));

    documento->dado = dado;
    documento->imprimeNaTela = imprimeNaTela;
    documento->ImprimeEmArquivo = ImprimeEmArquivo;
    documento->desaloca = desaloca;

    return documento;
}

void desalocaDocumento(tDocumento *doc) {
    if (!doc) return;
    doc->desaloca(doc->dado);
    free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc) {
    if (!doc) return;
    doc->imprimeNaTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path) {
    if (!doc) return;
    doc->ImprimeEmArquivo(doc->dado, path);
}