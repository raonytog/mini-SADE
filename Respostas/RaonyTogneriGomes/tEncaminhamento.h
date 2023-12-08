#ifndef _TENCAMINHAMENTO_H_
#define _TENCAMINHAMENTO_H_

typedef struct tEncaminhamento tEncaminhamento;

tEncaminhamento * CriaEncaminhamento (char * nomePaciente, char * CPF, char * especialidade, char * motivo, char *nomeMedico, char *CRM, char *data);

void DesalocaEncaminhamento (void * data);

void ImprimeEncaminhamentoTela (void * data);

void ImprimeEncaminhamentoArquivo (void * data, char * path);
                                
#endif // !_TENCAMINHAMENTO_H_