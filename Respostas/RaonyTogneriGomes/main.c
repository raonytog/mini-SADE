/* da linguagem*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* */
#include "tReceita.h"
#include "tDocumento.h"
#include "tFila.h"

#include "tBiopsia.h"

int main (int agrc, char * argv[]) { /* main oficial */
    if (agrc <= 1) {
        printf("ERRO: diretorio de arquivos nao informado\n");
        exit(1);
    }

    char diretorio[1001];
    sprintf(diretorio, "%s", argv[1]);

// int main () { /* main de testes */
//     char diretorio[1001] = "Casos/1";
// 

    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ################################################\n");


    return 0;
}

/** metas do dia
 * data
 * relatorio 
 * cadastro/login 
 * bd
**/