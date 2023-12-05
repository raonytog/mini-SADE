#ifndef _TLOGIN_H_
#define _TLOGIN_H_

#include <stdbool.h>

typedef struct tLogin tLogin;



tLogin * CriaLogin ();

void DesalocaLogin (tLogin * login);

bool VerificaUser (tLogin * login, char * usuario);

bool VerificaSenha (tLogin * login, char * senha);

#endif 
 