#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tPessoa.h"
#include "tLogin.h"

typedef enum {
    ADMIN = 1,
    USER = 0
} PODER_USUARIO;

typedef struct tSecretario tSecretario;

tSecretario * CriaSecretario ();

void DesalocaSecretario(tSecretario * secretario);

tLogin * ObtemLoginSecretario (tSecretario * secretario);

bool SecretarioEhUser (tSecretario * secretario);

bool SecretarioEhAdmin (tSecretario * secretario);

#endif