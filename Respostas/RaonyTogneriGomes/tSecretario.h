#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tPessoa.h"
#include "tLogin.h"

typedef struct tSecretario tSecretario;

tSecretario * CriaSecretario ();

void DesalocaSecretario(tSecretario * secretario);

bool SecretarioEhUser (tSecretario * secretario);

bool SecretarioEhAdmin (tSecretario * secretario);

#endif