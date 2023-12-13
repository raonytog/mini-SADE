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
#include "tRelatorioGeral.h"

/* tipos auxiliares criados*/
#include "tLesao.h"
#include "tPessoa.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tLogin.h"
#include "tConsulta.h"
#include "tMenu.h"

int main (int agrc, char * argv[]) { /* main ofc */
    char path[500], rPath[500], pathSaida[1000], pathBancoDados[1000];
    if (agrc <= 1) {
        printf("ERRO: diretorio de arquivos nao informado\n");
        exit(1);
    }

    strcpy(path, argv[1]);

// int main () { /* main de testes */
//     char path[500], rPath[500], pathSaida[1000], pathBancoDados[1000];
//     strcpy(path, "Casos/1");

    int qtdPessoas = 0, qtdMedicos = 0, qtdSecretarios = 0, qtdConsultas = 0;
    sprintf(pathSaida, "%s/saida", path);

    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%[^\n]%*c", rPath);
    printf("################################################\n");
    printf("Caminho do banco de dados: %s\n", rPath);
    printf("Caminho da pasta de saida: %s\n", pathSaida);
    sprintf(pathBancoDados, "%s/%s", path ,rPath);

    /** Recupera as informacoes dos binarios */
    char pessoasBin[2001];      sprintf(pessoasBin, "%s/pessoas.bin", pathBancoDados);
    char medicosBin[2001];      sprintf(medicosBin, "%s/medicos.bin", pathBancoDados);
    char secretariosBin[2001];  sprintf(secretariosBin, "%s/secretarios.bin", pathBancoDados);
    char consultasBin[2001];    sprintf(consultasBin, "%s/consultas.bin", pathBancoDados);

    FILE * fPessoas = fopen(pessoasBin, "rb");
    FILE * fSecretarios = fopen(secretariosBin, "rb"); 
    FILE * fMedicos = fopen(medicosBin, "rb"); 
    FILE * fConsultas = fopen(consultasBin, "rb"); 

    tPessoa ** pessoas = NULL;
    if (fPessoas) {
        pessoas = RecuperaPessoas(fPessoas, &qtdPessoas);
        fclose(fPessoas);
    }

    tMedico * medicoNULL = CriaMedicoNULL();
    tMedico ** medicos = NULL;
    if (fMedicos) {
        medicos = RecuperaMedicos(fMedicos, &qtdMedicos);
        fclose(fMedicos);
    }

    tSecretario ** secretarios = NULL;
    if (fSecretarios) {
        secretarios = RecuperaSecretario(fSecretarios, &qtdSecretarios);
        fclose(fSecretarios);
    }

    tConsulta ** consultas = NULL;
    if (fConsultas) {
        consultas = RecuperaConsulta(fConsultas, &qtdConsultas);
        fclose(fConsultas);
    }

    tListaPessoas * listaBusca =  NULL;
    tFila * fila = criaFila();

    /** se nao houver secretarios no banco, cadastra, obrigartoriamente, o secretario*/
    if (qtdSecretarios == 0) {
        printf("#################### CADASTRO SECRETARIO #######################\n");
        qtdSecretarios++;
        secretarios = realloc(secretarios, qtdSecretarios * sizeof(tSecretario *));
        secretarios[qtdSecretarios-1] = CriaSecretario();
    }
    
    /** verifia login do agente */
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
    int opcaoMenu = 0, indiceConsulta = 0, sair = 0, achouPessoa = 0;
    while (1) {
        sair = 0;
        ImprimeMenu(cargo);
        scanf("%d%*c", &opcaoMenu);

        switch (opcaoMenu) {
            case CADASTRAR_SECRETARIO:
                if (cargo == MEDICO || cargo == USER) break;

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
                if (cargo == MEDICO) break; 
                printf("#################### CADASTRO MEDICO #######################\n");
                qtdMedicos++;
                medicos = realloc(medicos, qtdMedicos * sizeof(tMedico *));
                medicos[qtdMedicos-1] = CriaMedico();

                if (ExisteMedicoCpf(medicos, qtdMedicos, medicos[qtdMedicos-1])) {
                    DesalocaMedico(medicos[qtdMedicos-1]);
                    qtdMedicos--;
                    medicos = realloc(medicos, qtdMedicos * sizeof(tMedico *));
                    printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");

                } else { // se nao existir medico
                    printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    printf("###############################################################\n");
                    scanf("%*c");
                }
                break;



            case CADASTRAR_PACIENTE:
                if (cargo == MEDICO) break;
                printf("#################### CADASTRO PACIENTE #######################\n");
                qtdPessoas++;
                pessoas = realloc(pessoas, qtdPessoas * sizeof(tPessoa *));
                pessoas[qtdPessoas-1] = CriaPessoa();

                if (ExistePessoaCpf(pessoas, qtdPessoas, pessoas[qtdPessoas-1])) {
                    DesalocaPessoa(pessoas[qtdPessoas-1]);
                    qtdPessoas--;
                    pessoas = realloc(pessoas, qtdPessoas * sizeof(tPessoa *));
                    printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");

                } else { // se nao tiver pessoa nenhuma com o cpf 
                    printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    printf("###############################################################\n");
                    scanf("%*c");
                }
                break;



            case REALIZAR_CONSULTA:
                if (cargo == USER) break;
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("CPF DO PACIENTE: ");                     scanf("%[^\n]%*c", cpf);
                printf("---\n");

                for (indiceConsulta = 0; indiceConsulta < qtdPessoas; indiceConsulta++) {
                    if (strcmp(ObtemCPFPessoa(pessoas[indiceConsulta]), cpf) == 0) {
                        qtdConsultas++;
                        consultas = realloc(consultas, qtdConsultas * sizeof(tConsulta *));

                        printf("-NOME: %s\n", ObtemNomePessoa(pessoas[indiceConsulta]));
                        printf("-DATA DE NASCIMENTO: %s\n", ObtemDataPessoa(pessoas[indiceConsulta]));
                        printf("---\n");

                        if (cargo != MEDICO) { // se for secretario
                            consultas[qtdConsultas-1] = CriaConsulta(pessoas[indiceConsulta], medicoNULL);
                            ExecutaConsulta(consultas[qtdConsultas-1], fila, 0);

                        } else { // se for medico mesmo
                            consultas[qtdConsultas-1] = CriaConsulta(pessoas[indiceConsulta], medicos[indiceMedicoLogado]);
                            ExecutaConsulta(consultas[qtdConsultas-1], fila, 1);
                        }
                        sair++;
                    }
                    if (sair) break;
                }

                if (!sair) {
                    printf("PACIENTE SEM CADASTRO\n");
                    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    printf("###############################################################\n");
                    scanf("%*c");
                }
                break;



            case BUSCAR_PACIENTES:
                achouPessoa = 0;
                printf("#################### BUSCAR PACIENTES #######################\n");
                printf("NOME DO PACIENTE: ");               scanf("%[^\n]%*c", nomePacienteBusca);

                int stop = 0;
                for (int i = 0; i < qtdPessoas; i++) {
                    if (strcmp(nomePacienteBusca, ObtemNomePessoa(pessoas[i])) == 0) {
                        if (!stop) listaBusca =  CriaListaBusca();
                        AdiconaPessoaLista(listaBusca, pessoas[i]);
                        achouPessoa++;
                        stop = 1;
                    }
                }

                if (!achouPessoa) {
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    scanf("%*c");

                } else { // se achou pessoa
                    ImprimeNomeRequisitadoTela(listaBusca);
                    ImprimeMenuBuscarPacientes(fila, listaBusca);
                }
                break;



            case RELATORIO_GERAL:
                ExecutaRelatorioGeral(fila, pessoas, qtdPessoas, consultas, qtdConsultas, pathSaida);
                break;



            case FILA_DE_IMPRESSAO:
                while (1) {
                    ImprimeMenuFilaImpressao();
                    scanf("%d%*c", &opcaoMenu);
                    switch (opcaoMenu) {
                        case 1:
                            printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
                            imprimeFila(fila, pathSaida);
                            printf("\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR\n");
                            printf("############################################################\n");
                            scanf("%*c");
                            break;

                        case 2:
                            sair++;
                            break;
                    }
                    if (sair) break;
                }
                break;



            case FINALIZAR_O_PROGRAMA:
                SalvaPessoaBinario(pessoas, qtdPessoas, pathBancoDados);
                SalvaMedicoBinario(medicos, qtdMedicos, pathBancoDados);
                SalvaSecretarioBinario(secretarios, qtdSecretarios, pathBancoDados);
                SalvaConsultaBinario(consultas, qtdConsultas, pathBancoDados); // salva a lesao bin tb
                
                for (int i = 0; i < qtdPessoas; i++) {
                    DesalocaPessoa(pessoas[i]);
                    pessoas[i] = NULL;
                }
                free(pessoas);

                for (int i = 0; i < qtdMedicos; i++) {
                    DesalocaMedico(medicos[i]);
                    medicos[i] = NULL;
                }
                DesalocaMedico(medicoNULL);
                medicoNULL = NULL;
                free(medicos);
                medicos = NULL;

                for (int i = 0; i < qtdSecretarios; i++) {
                    DesalocaSecretario(secretarios[i]);
                    secretarios[i] = NULL;
                }
                free(secretarios);
                secretarios = NULL;

                for (int i = 0; i < qtdConsultas; i++) {
                    DesalocaConsulta(consultas[i]);
                    consultas[i] = NULL;
                }
                free(consultas);
                consultas = NULL;

                desalocaFila(fila);
                
                exit(1);
                break;
        }
   }
    
    return 0;
}