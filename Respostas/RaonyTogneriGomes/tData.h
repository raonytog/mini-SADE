#ifndef _TDATA_H_
#define _TDATA_H_

typedef struct tData tData;

tData * LeData ();

tData * LeDataConsulta ();

const char * ObtemDataString (tData * data);

void ImprimeData (tData * data);

int CalculaIdade(tData * data);

#endif // !_TDATA_H_

