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
#include "tConsulta.h"

void ImprimeMenuInicial () {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("    (1) CADASTRAR SECRETARIO\n");
    printf("    (2) CADASTRAR MEDICO\n");
    printf("    (3) CADASTRAR PACIENTE\n");
    printf("    (4) REALIZAR CONSULTA\n");
    printf("    (5) BUSCAR PACIENTES\n");
    printf("    (6) RELATORIO GERAL\n");
    printf("    (7) FILA DE IMPRESSAO\n");
    printf("    (8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

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

// int main (int agrc, char * argv[]) {
//     if (agrc <= 1) {
//         printf("ERRO: diretorio de arquivos nao informado\n");
//         exit(1);
//     }

//     sprintf(path, "%s", argv[1]);
//     sprintf(pathSaida, "%s/saida", argv[1]);

int main () { /* main de testes */
    char diretorio[1001] = "Casos/1";


    char path[1001], bdPath[1001], pathSaida[1001];
    int qtdPessoas = 0, qtdMedicos = 0, qtdSecretarios = 0;
    tPessoa ** pessoas = NULL;
    tMedico ** medicos = NULL;
    tSecretario ** secretarios = NULL;
    tListaPessoas * listaBusca =  NULL;
    tConsulta * consulta = NULL;
    tFila * fila = NULL;

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

    qtdSecretarios++;
    secretarios = realloc(secretarios, qtdSecretarios * sizeof(tSecretario *));
    secretarios[qtdSecretarios-1] = CriaSecretario();

    /**
     * tem q verificar login
    */

    int opcaoMenu = 0;
    char nomePacienteBusca[100], cpf[15];
    while (1) {
        ImprimeMenuInicial();
        scanf("%d%*c", &opcaoMenu);
        switch (opcaoMenu) {
            
            case CADASTRAR_SECRETARIO:
                printf("#################### CADASTRO SECRETARIO #######################\n");
                qtdSecretarios++;
                secretarios = realloc(secretarios, qtdSecretarios * sizeof(tSecretario *));
                secretarios[qtdSecretarios-1] = CriaSecretario();

                printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                printf("###############################################################\n");
                scanf("%*c");
                break;



            case CADASTRAR_MEDICO:
                printf("#################### CADASTRO MEDICO #######################\n");
                qtdMedicos++;
                medicos = realloc(medicos, qtdMedicos * sizeof(tMedico *));
                medicos[qtdMedicos-1] = CriaMedico();

                printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                printf("###############################################################\n");
                scanf("%*c");
                break;



            case CADASTRAR_PACIENTE:
                printf("#################### CADASTRO PACIENTE #######################\n");
                qtdPessoas++;
                pessoas = realloc(pessoas, qtdPessoas * sizeof(tPessoa *));
                pessoas[qtdPessoas-1] = CriaPessoa();

                printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                printf("###############################################################\n");
                scanf("%*c");
                break;



            case REALIZAR_CONSULTA:
                scanf("%[^\n]%*c", cpf);
                break;



            case BUSCAR_PACIENTES:
                listaBusca =  CriaListaBusca();
                printf("NOME DO PACIENTE: ");        scanf("%[^\n]%*c", nomePacienteBusca);

                for (int i = 0; i < qtdPessoas; i++) {
                    if (strcmp(nomePacienteBusca, ObtemNomePessoa(pessoas[i])) == 0) AdiconaPessoaLista(listaBusca, pessoas[i]);
                }

                if (ObtemNumeroPessoasLista(listaBusca) == 0) {
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");


                } else {  
                    
                    ImprimeNomeRequisitadoTela(listaBusca);
                    ImprimeNomeRequisitadoArquivo(listaBusca, path); 
                }


                break;



            case RELATORIO_GERAL:
                /* to do*/
                break;



            case FILA_DE_IMPRESSAO:
                printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
                printf("ESCOLHA UMA OPCAO:\n");
                printf("(1) EXECUTAR FILA DE IMPRESSAO\n");
                printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                printf("############################################################\n");
                scanf("%d", &opcaoMenu);

                switch (opcaoMenu) {
                    case 1:
                        imprimeFila(fila, path);
                        break;

                    case 2:
                        break;
                }
                break;



            case FINALIZAR_O_PROGRAMA:
                for (int i = 0; i < qtdPessoas; i++)
                    DesalocaPessoa(pessoas[i]);
                if (pessoas) free(pessoas);

                for (int i = 0; i < qtdMedicos; i++)
                    DesalocaMedico(medicos[i]);
                if (medicos) free(medicos);

                for (int i = 0; i < qtdSecretarios; i++)
                    DesalocaSecretario(secretarios[i]);
                if (secretarios) free(secretarios);

                DesalocaLista(listaBusca);
                DesalocaConsulta(consulta);
                desalocaFila(fila);
                exit(1);
                break;
        }
    }
    
    return 0;
}

/** metas do dia
 * consulta             --
 * cadastro/login       -
 * main                 -
 * relatorio geral
 * binario
**/