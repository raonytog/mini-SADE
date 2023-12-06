#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct tPessoa tPessoa;

typedef struct tListaPessoa tListaPessoa;

typedef enum {
    NAO_EXISTE = 0,
    SECRETARIO = 1,
    MEDICO = 2,
    PACIENTE = 3
} CARGO;

tPessoa * CriaPessoa ();

void DesalocaPessoa (void * dado);

tData * ObtemDataPessoa (tPessoa * pessoa);

const char * ObtemNomePessoa (tPessoa * pessoa);

const char * ObtemCPFPessoa (tPessoa * pessoa);

const char * ObtemTelefonePessoa (tPessoa * pessoa);

const char * ObtemGeneroPessoa (tPessoa * pessoa);

CARGO ObtemCargoPessoa (tPessoa * pessoa);

#endif
