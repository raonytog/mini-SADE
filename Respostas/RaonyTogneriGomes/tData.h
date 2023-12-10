#ifndef _TDATA_H_
#define _TDATA_H_

#include <stdio.h>

typedef struct tData tData;

tData * LeData ();

tData * LeDataConsulta ();

tData * CriaDataNULL ();

void DesalocaData (tData * data);

char * ObtemDataString (tData * data);

void ImprimeData (tData * data);

int CalculaIdade(tData * data);

void SalvaData (tData * data, FILE * arquivo);

tData * RecuperaData (FILE * arquivo);

#endif // !_TDATA_H_

