#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tPessoa.h"
#include "tLogin.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct tSecretario tSecretario;

/**
 * Cria um secretario valido a partir das informacoes lidas do terminal
*/
tSecretario * CriaSecretario ();

/**
 * Desaloca secretario caso exista
*/
void DesalocaSecretario(tSecretario * secretario);

/**
 * verifica se existe um secretario com o cpf do secretario em analise
*/
bool ExisteSecretarioCpf(tSecretario ** secretarios, int qtdSecretarios, tSecretario * secretarioEmAnalise);

/**
 * Verifica se o secretario tem permisao de usuario (nao eh um administrador)
*/
bool SecretarioEhUser (tSecretario * secretario);

/**
 * Verifica se o secretario tem poder administrativo
*/
bool SecretarioEhAdmin (tSecretario * secretario);

/**
 * Obtem login do secretario passado
*/
tLogin * ObtemSecretarioLogin (tSecretario * secretario);

/**
 *  Salva um unico secretario no binario
 */
void SalvaSecretario (tSecretario * secretario, FILE * arquivo);

/**
 * Recupera a lista e a qtd de secretarios do binario secretarios.bin
*/
tSecretario ** RecuperaSecretario (FILE * arquivo, int * qtdSecretarios);

/** 
 * Salva todos os secretarios e a qtd deles no binario
*/
void SalvaSecretarioBinario (tSecretario ** secretarios, int qtdSecretarios, char * path);

#endif