#ifndef _TENCAMINHAMENTO_H_
#define _TENCAMINHAMENTO_H_

typedef struct tEncaminhamento tEncaminhamento;

/**
 * Cria o encaminhamento valido
*/
tEncaminhamento * CriaEncaminhamento (char * nomePaciente, char * CPF, char * especialidade, char * motivo, char *nomeMedico, char *CRM, char *data);

/**
 * Desaloca o encaminhamento
*/
void DesalocaEncaminhamento (void * data);

/**
 * Imprime o encaminhamento na tela
*/
void ImprimeEncaminhamentoTela (void * data);

/**
 * Imprime o encaminhamento no arquivo
*/
void ImprimeEncaminhamentoArquivo (void * data, char * path);
                                
#endif // !_TENCAMINHAMENTO_H_