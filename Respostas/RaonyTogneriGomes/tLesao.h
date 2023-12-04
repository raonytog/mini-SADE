
//L1 - NEVO - DORSO - 10MM

#ifndef _TLESAO_H_
#define _TLESAO_H_

typedef struct tLesao tLesao;

tLesao * CriaLesao ();

void ImprimeLesaoTela (tLesao * lesao);

void ImprimeLesaoArquivo (tLesao * lesao, char * path);

void DesalocaLesao (tLesao * lesao);

int NecessitaCirurgia (tLesao * lesao);

int NecessitaCrioterapia (tLesao * lesao);

int TamanhoLesao (tLesao * lesao);

#endif
