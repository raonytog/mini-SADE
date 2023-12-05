#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct tPessoa tPessoa;

tPessoa * CriaPessoa();

void DesalocaPessoa(tPessoa * pessoa);

const char * ObtemNomePessoa (tPessoa * pessoa);

const char * ObtemCPFPessoa (tPessoa * pessoa);

#endif
