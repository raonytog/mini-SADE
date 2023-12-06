#include "tData.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tData {
    int dia, mes, ano;
    char dataString[10];
};


tData * LeData() {
    tData * data = malloc(sizeof(tData));

    printf("DATA DE NASCIMENTO: ");
    scanf("%d/%d/%d", &data->dia, &data->mes, &data->ano);
    sprintf(data->dataString, "%d/%d/%d", data->dia, data->mes, data->ano);

    return data;
}

tData * LeDataConsulta () {
    tData * data = malloc(sizeof(tData));

    printf("DATA DA CONSULTA: ");
    scanf("%d/%d/%d", &data->dia, &data->mes, &data->ano);
    sprintf(data->dataString, "%d/%d/%d", data->dia, data->mes, data->ano);

    return data;
}

void ImprimeData (tData * data) {
    printf("%d/%d/%d", data->dia, data->mes, data->ano);
}

int CalculaIdade(tData * data);