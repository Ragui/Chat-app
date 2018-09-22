#ifndef serverRecoverPassword_H
#define serverRecoverPassword_H
#include "serverDataStruct.h"

bool validRecover(const char *username,int question, const char *Answer ,char *errorMessage);


#endif
