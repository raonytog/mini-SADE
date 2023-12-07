#ifndef _TLOGIN_H_
#define _TLOGIN_H_

#include <stdbool.h>
#include "tPessoa.h"
#include "tMedico.h"
#include "tSecretario.h"

typedef struct tLogin tLogin;

tLogin * CriaLogin ();

void DesalocaLogin (tLogin * login);

bool VerificaUser (tLogin * login, char * usuario);

bool VerificaSenha (tLogin * login, char * senha);

bool VerificaLogin (tLogin * login, char * usuario, char * senha);

bool CadastradoAnteriormente (void ** data, int qtd, char tipo, void * analisado);

#endif 
 