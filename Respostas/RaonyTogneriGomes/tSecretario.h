#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tPessoa.h"
#include "tLogin.h"

typedef struct tSecretario tSecretario;

tSecretario * CriaSecretario ();

void DesalocaSecretario(tSecretario * secretario);

const char * ObtemCRM (tSecretario * secretario);

tLogin * ObtemLogin(tSecretario * secretario);

#endif