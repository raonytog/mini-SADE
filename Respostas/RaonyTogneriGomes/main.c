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
 * **/

/* tipos auxiliares criados*/
#include "tLesao.h"
#include "tPessoa.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tLogin.h"
#include "tConsulta.h"
#include "tMenu.h"

int main (int agrc, char * argv[]) {
    char path[1001], bdPath[1001], pathSaida[1001];
    if (agrc <= 1) {
        printf("ERRO: diretorio de arquivos nao informado\n");
        exit(1);
    }

    sprintf(path, "%s", argv[1]);
    sprintf(pathSaida, "%s/saida", argv[1]);

    // int main () { /* main de testes */
    // char path[1001], bdPath[1001], pathSaida[1001] = "Casos/1";

    int qtdPessoas = 0, qtdMedicos = 0, qtdSecretarios = 0, qtdConsultas = 0;
    tPessoa ** pessoas = NULL;
    tMedico ** medicos = NULL;          tMedico * medicoNULL = NULL;
    tSecretario ** secretarios = NULL;
    tListaPessoas * listaBusca =  NULL;
    tConsulta ** consultas = NULL;
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

    printf("#################### CADASTRO SECRETARIO #######################\n");
    qtdSecretarios++;
    secretarios = realloc(secretarios, qtdSecretarios * sizeof(tSecretario *));
    secretarios[qtdSecretarios-1] = CriaSecretario();

    CARGO_LOGADO cargo;
    char login[20], password[20];
    while (1) {
        printf("######################## ACESSO MINI-SADE ######################\n");
        printf("DIGITE SEU LOGIN: ");       scanf("%[^\n]%*c", login);
        printf("DIGITE SUA SENHA: ");       scanf("%[^\n]%*c", password);
        printf("###############################################################\n");

        cargo = VerificaAutenticacao(medicos, qtdMedicos, secretarios, qtdSecretarios, login, password);
        if (cargo != FALHA) break;
        printf("###############################################################\n");
        printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    }

    int indiceMedicoLogado = 0, indiceSecretarioLogado = 0;
    if (cargo == MEDICO) {
        indiceMedicoLogado = EncontraIndiceMedicoLogado(medicos, qtdMedicos, login, password);

    } else indiceSecretarioLogado = EncontraIndiceSecretarioLogado(secretarios, qtdSecretarios, login, password);

    char nomePacienteBusca[100], cpf[15];
    int opcaoMenu = 0, indiceConsulta = 0;
    while (1) {
        ImprimeMenu(cargo);
        scanf("%d%*c", &opcaoMenu);

        switch (opcaoMenu) {
            case CADASTRAR_SECRETARIO:
                if (cargo != ADMIN) break;

                printf("#################### CADASTRO SECRETARIO #######################\n");
                qtdSecretarios++;
                secretarios = realloc(secretarios, qtdSecretarios * sizeof(tSecretario *));
                secretarios[qtdSecretarios-1] = CriaSecretario();

                if (ExisteSecretarioCpf(secretarios, qtdSecretarios, secretarios[qtdSecretarios-1])) {
                    DesalocaSecretario(secretarios[qtdSecretarios-1]);
                    qtdSecretarios--;
                    secretarios = realloc(secretarios, qtdSecretarios * sizeof(tSecretario *));
                    printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");

                } else {
                    printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    printf("###############################################################\n");
                    scanf("%*c");
                }
                break;



            case CADASTRAR_MEDICO:
                printf("#################### CADASTRO MEDICO #######################\n");
                qtdMedicos++;
                medicos = realloc(medicos, qtdMedicos * sizeof(tMedico *));
                medicos[qtdMedicos-1] = CriaMedico();

                if (ExisteMedicoCpf(medicos, qtdMedicos, medicos[qtdMedicos-1])) {
                    DesalocaMedico(medicos[qtdMedicos-1]);
                    qtdMedicos--;
                    medicos = realloc(medicos, qtdMedicos * sizeof(tMedico *));
                    printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");

                } else {
                    printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    printf("###############################################################\n");
                    scanf("%*c");
                }
                break;



            case CADASTRAR_PACIENTE:
                printf("#################### CADASTRO PACIENTE #######################\n");
                qtdPessoas++;
                pessoas = realloc(pessoas, qtdPessoas * sizeof(tPessoa *));
                pessoas[qtdPessoas-1] = CriaPessoa();

                if (ExistePessoaCpf(pessoas, qtdPessoas, pessoas[qtdPessoas-1])) {
                    DesalocaPessoa(pessoas[qtdPessoas-1]);
                    qtdPessoas--;
                    pessoas = realloc(pessoas, qtdPessoas * sizeof(tPessoa *));
                    printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");

                } else {
                    printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    printf("###############################################################\n");
                    scanf("%*c");
                }
                break;



            case REALIZAR_CONSULTA:
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("CPF DO PACIENTE: ");                     scanf("%[^\n]%*c", cpf);
                printf("---\n");

                for (indiceConsulta = 0; indiceConsulta < qtdPessoas; indiceConsulta++) {
                    if (strcmp(ObtemCPFPessoa(pessoas[indiceConsulta]), cpf) == 0) {
                        qtdConsultas++;
                        consultas = realloc(consultas, qtdConsultas * sizeof(tConsulta *));

                        printf("-NOME: %s\n", ObtemNomePessoa(pessoas[indiceConsulta]));
                        printf("-DATA DE NASCIMENTO: %s\n", ObtemDataString( ObtemDataPessoa(pessoas[indiceConsulta]) ));
                        printf("---\n");


                        if (cargo != MEDICO) { // se for secretario
                            consultas[qtdConsultas-1] = CriaConsulta(pessoas[indiceConsulta], medicoNULL);
                            ExecutaConsulta(consultas[qtdConsultas-1], fila);

                        } else { // se for medico mesmo
                            consultas[qtdConsultas-1] = CriaConsulta(pessoas[indiceConsulta], medicos[indiceMedicoLogado]);
                            ExecutaConsulta(consultas[qtdConsultas-1], fila);
                        }

                        break;
                    }
                }

                printf("PACIENTE SEM CADASTRO\n");
                printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                printf("###############################################################\n");
                scanf("%*c");
                break;

            case BUSCAR_PACIENTES:
                printf("#################### BUSCAR PACIENTES #######################\n");
                listaBusca =  CriaListaBusca();
                printf("NOME DO PACIENTE: ");               scanf("%[^\n]%*c", nomePacienteBusca);

                for (int i = 0; i < qtdPessoas; i++)
                    if (strcmp(nomePacienteBusca, ObtemNomePessoa(pessoas[i])) == 0) AdiconaPessoaLista(listaBusca, pessoas[i]);

                if (ObtemNumeroPessoasLista(listaBusca) == 0) {
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");

                } else {
                    ImprimeNomeRequisitadoTela(listaBusca);
                    ImprimeNomeRequisitadoArquivo(listaBusca, pathSaida); 
                    ImprimeMenuBuscarPacientes(fila, listaBusca);
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
                        imprimeFila(fila, pathSaida);
                        break;

                    case 2:
                        break;
                }
                break;



            case FINALIZAR_O_PROGRAMA:
                for (int i = 0; i < qtdPessoas; i++)
                    DesalocaPessoa(pessoas[i]);
                free(pessoas);

                for (int i = 0; i < qtdMedicos; i++)
                    DesalocaMedico(medicos[i]);
                free(medicos);

                for (int i = 0; i < qtdSecretarios; i++)
                    DesalocaSecretario(secretarios[i]);
                free(secretarios);

                for (int i = 0; i < qtdConsultas; i++)
                    DesalocaConsulta(consultas[i]);
                free(consultas);

                DesalocaLista(listaBusca);
                desalocaFila(fila);
                exit(1);
                break;
        }
   }
    
    return 0;
}

/** metas do trabalho
 * main                 -
 * relatorio geral
 * binario
**/