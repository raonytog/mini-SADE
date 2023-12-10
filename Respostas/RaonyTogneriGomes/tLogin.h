#ifndef _TLOGIN_H_
#define _TLOGIN_H_

typedef struct tMedico tMedico;
typedef struct tSecretario tSecretario;

#include <stdbool.h>
#include "tPessoa.h"
#include "tMedico.h"
#include "tSecretario.h"

typedef struct tLogin tLogin;

typedef enum {
    FALHA = 0,
    ADMIN = 1,
    MEDICO = 2,
    USER = 3
} CARGO_LOGADO;

tLogin * CriaLogin ();

tLogin * CriaLoginNULL ();

void DesalocaLogin (tLogin * login);

CARGO_LOGADO VerificaAutenticacao (tMedico ** medicos, int qtdMedicos, 
                           tSecretario ** secretarios, int qtdSecretarios,
                           char * user, char * password);

int EncontraIndiceMedicoLogado (tMedico ** medicos, int qtdMedicos, char * user, char * password);

int EncontraIndiceSecretarioLogado (tSecretario ** secretarios, int qtdSecretarios, char * user, char * password);

bool VerificaUser (tLogin * login, char * usuario);

bool VerificaSenha (tLogin * login, char * senha);

bool VerificaUsuarioESenha (tLogin * login, char * usuario, char * senha);

bool CadastradoAnteriormente (void ** data, int qtd, char tipo, void * analisado);

void SalvaLogin (tLogin * login, FILE * arquivo);

tLogin * RecuperaLogin (FILE * arquivo);


#endif 
 