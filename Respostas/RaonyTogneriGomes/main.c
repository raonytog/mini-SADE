/* da linguagem*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* .h ofertados */
#include "tReceita.h"
#include "tDocumento.h"
#include "tFila.h"

/* arquivos de saida.txt*/
#include "tBiopsia.h"
#include "tEncaminhamento.h"
#include "tListaPessoas.h"
#include "tReceita.h"
/** faltando:
 * relatorio geral 
 * saida 
 * **/

/* tipos auxiliares criados*/
#include "tLesao.h"
#include "tPessoa.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tLogin.h"

typedef enum {
    CADASTRAR_SECRETARIO = 1,
    CADASTRAR_MEDICO = 2,
    CADASTRAR_PACIENTE = 3,
    REALIZAR_CONSULTA = 4,
    BUSCAR_PACIENTES = 5,
    RELATORIO_GERAL = 6,
    FILA_DE_IMPRESSAO = 7,
    FINALIZAR_O_PROGRAMA = 8
} OPCOES_MENU;

int main (int agrc, char * argv[]) { /* main oficial */
    if (agrc <= 1) {
        printf("ERRO: diretorio de arquivos nao informado\n");
        exit(1);
    }

    char path[1001], bdPath[1001], pathSaida[1001];
    sprintf(path, "%s", argv[1]);
    sprintf(pathSaida, "%s/saida", path);

// int main () { /* main de testes */
//     char diretorio[1001] = "Casos/1";
// 

    int qtdPessoas = 0, qtdMedicos = 0, qtdSecretarios = 0;
    tPessoa ** pessoas = NULL;
    tMedico ** medicos = NULL;
    tSecretario ** secretarios = NULL;
    tListaPessoas * listaBusca =  NULL;

    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%[^\n]%*c", bdPath);
    printf("################################################\n");
    printf("Caminho do banco de dados: %s\n", bdPath);
    printf("Caminho da pasta de saida: %s\n", pathSaida);

    /** verificar se existe um bd 
     * caso exista, verificar login até o user e senha serem validos
     * caso nao, obrigar criar um secretario de nivel adm
     * **/

    printf("#################### CADASTRO SECRETARIO #######################\n");
    qtdSecretarios++;
    secretarios[qtdSecretarios] = CriaSecretario();
    printf("###############################################################");

    int opcaoMenu = 0; char nomePacienteBusca[100];
    while (1) {
        /* menu*/
        scanf("%d", &opcaoMenu);
        switch (opcaoMenu) {
            case CADASTRAR_SECRETARIO:
                qtdSecretarios++;
                secretarios = malloc(qtdSecretarios * sizeof(tSecretario *));
                secretarios[qtdSecretarios-1] = malloc(sizeof(tSecretario *));
                /* to do*/
                break;

            case CADASTRAR_MEDICO:
                qtdMedicos++;
                medicos = malloc(qtdMedicos * sizeof(tMedico *));
                medicos[qtdMedicos-1] = malloc(sizeof(tMedico *));
                /* to do*/
                break;

            case CADASTRAR_PACIENTE:
                qtdPessoas++;
                pessoas = malloc(qtdPessoas * sizeof(tPessoa *));
                pessoas[qtdPessoas-1] = malloc(sizeof(tPessoa *));
                /* to do*/
                break;

            case REALIZAR_CONSULTA:
                /* to do*/
                break;

            case BUSCAR_PACIENTES:
                listaBusca =  CriaListaBusca();
                printf("#################### BUSCAR PACIENTES #######################\n");
                printf("NOME DO PACIENTE:");        scanf("%[^\n]\n", nomePacienteBusca);

                for (int i = 0; i < qtdPessoas; i++) 
                    AdiconaPessoaLista(listaBusca, pessoas[i], nomePacienteBusca);
            
                printf("#################### BUSCAR PACIENTES #######################\n");
                if (ObtemNumeroPessoasLista(listaBusca) == 0) 
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR ");

                else {
                    ImprimeNomeRequisitadoTela(listaBusca, nomePacienteBusca);
                    ImprimeNomeRequisitadoArquivo(listaBusca, nomePacienteBusca, pathSaida);
                }
                printf("############################################################\n");
                break;

            case RELATORIO_GERAL:
                /* to do*/
                break;

            case FILA_DE_IMPRESSAO:
                /* to do*/
                break;

            case FINALIZAR_O_PROGRAMA:
                /* precisa desalocar */
                exit(1);
                break;
        }
    }
    
    return 0;
}

/** metas do dia
 * consulta
 * cadastro/login
 * main
 * relatorio geral
 * binario
**/