#ifndef _TLOGIN_H_
#define _TLOGIN_H_

typedef struct tMedico tMedico;
typedef struct tSecretario tSecretario;

#include <stdbool.h>
#include <stdio.h>
#include "tPessoa.h"
#include "tMedico.h"
#include "tSecretario.h"

typedef struct tLogin tLogin;

/**
 * enum de agentes que podem estar logados
*/
typedef enum {
    FALHA = 0,
    ADMIN = 1,
    MEDICO = 2,
    USER = 3
} CARGO_LOGADO;

/**
 * Cria e le o login de um secretario ou medico
*/
tLogin * CriaLogin ();

/**
 * Cria um login com '\0'
*/
tLogin * CriaLoginNULL ();

/**
 * Desaloca o login, caso exista
*/
void DesalocaLogin (tLogin * login);

/**
 * Retorna o cargo da pessoa que esta logada no sistema
*/
CARGO_LOGADO VerificaAutenticacao (tMedico ** medicos, int qtdMedicos, 
                           tSecretario ** secretarios, int qtdSecretarios,
                           char * user, char * password);

/**
 * Encontra o indice do medico logado
*/
int EncontraIndiceMedicoLogado (tMedico ** medicos, int qtdMedicos, char * user, char * password);

/**
 * Encontra o indice do secretario logado
*/
int EncontraIndiceSecretarioLogado (tSecretario ** secretarios, int qtdSecretarios, char * user, char * password);

/**
 * Verifica se o usuario eh igual ao nome digitado
*/
bool VerificaUser (tLogin * login, char * usuario);

/**
 * Verifica se a senha eh igual a senha digitada
*/
bool VerificaSenha (tLogin * login, char * senha);

/**
 * Verifica se o login foi efetuado corretamente
*/
bool VerificaUsuarioESenha (tLogin * login, char * usuario, char * senha);

/**
 * Verifica se o usuario ja foi cadastrado
*/
bool CadastradoAnteriormente (void ** data, int qtd, char tipo, void * analisado);

/**
 * Salva o login no arquivo binario passado
*/
void SalvaLogin (tLogin * login, FILE * arquivo);

/**
 * Recupera o login do arquivo binario passado
*/
tLogin * RecuperaLogin (FILE * arquivo);


#endif 
 