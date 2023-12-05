
//L1 - NEVO - DORSO - 10MM

#ifndef _TLESAO_H_
#define _TLESAO_H_

typedef struct tLesao tLesao;

tLesao * CriaLesao ();


void ImprimeLesaoTela (tLesao * lesao);

void ImprimeLesaoArquivo (tLesao * lesao, FILE * arquivo);

void DesalocaLesao (tLesao * lesao);


const char * ObtemRotulo (tLesao * lesao);

const char * ObtemDiagnostico (tLesao * lesao);

const char * ObtemRegiaoCorpo (tLesao * lesao);


int NecessitaCirurgia (tLesao * lesao);

int NecessitaCrioterapia (tLesao * lesao);

int TamanhoLesao (tLesao * lesao);

#endif
