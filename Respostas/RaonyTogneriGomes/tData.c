#include "tData.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tData {
    int dia, mes, ano;
    char dataString[10];
};


tData * LeData() {
    tData * data = calloc(1, sizeof(tData));

    printf("DATA DE NASCIMENTO: ");
    scanf("%d/%d/%d%*c", &data->dia, &data->mes, &data->ano);
    sprintf(data->dataString, "%d/%d/%d", data->dia, data->mes, data->ano);

    return data;
}

tData * LeDataConsulta () {
    tData * data = calloc(1, sizeof(tData));
    if (!data) {
        printf("\nDATA EH NULL\n"); 
        return NULL;
    }

    printf("DATA DA CONSULTA: ");
    scanf("%d/%d/%d", &data->dia, &data->mes, &data->ano);
    sprintf(data->dataString, "%d/%d/%d", data->dia, data->mes, data->ano);

    return data;
}

void DesalocaData (tData * data) {
    if (!data) return;
    free(data);
    data = NULL;
}

char * ObtemDataString (tData * data) {
    char * d = data->dataString;
    return d;
}

void ImprimeData (tData * data) {
    printf("%d/%d/%d", data->dia, data->mes, data->ano);
}

int CalculaIdade(tData * data) {
    int dia = data->dia, 
        mes = data->mes, 
        ano = data->ano,
        idade = 2023 - ano;

    if (mes > 11 || (mes == 11 && dia >= 9)) idade++; 
    return idade;
}
//09/11/2023