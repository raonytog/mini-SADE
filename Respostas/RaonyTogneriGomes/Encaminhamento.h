#ifndef _ENCAMINHAMENTO_H_
#define _ENCAMINHAMENTO_H_

#include "tPessoa.h"
#include "tMedico.h"

void ImprimeEncaminhamentoTela (tPessoa * paciente, char * especialidade, char * motivo, 
                                tMedico * medico, char * data);

void ImprimeEncaminhamentoArquivo (tPessoa * paciente, char * especialidade, char * motivo, 
                                tMedico * medico, char * data, char * path);
                                
#endif // !_TENCAMINHAMENTO_H_