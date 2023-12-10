#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tPessoa.h"
#include "tLogin.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct tSecretario tSecretario;

tSecretario * CriaSecretario ();

void DesalocaSecretario(tSecretario * secretario);

bool ExisteSecretarioCpf(tSecretario ** secretarios, int qtdSecretarios, tSecretario * secretarioEmAnalise);

bool SecretarioEhUser (tSecretario * secretario);

bool SecretarioEhAdmin (tSecretario * secretario);

tLogin * ObtemSecretarioLogin (tSecretario * secretario);

void SalvaSecretario (tSecretario * secretario, FILE * arquivo);

tSecretario * RecuperaSecretario (FILE * arquivo);

#endif