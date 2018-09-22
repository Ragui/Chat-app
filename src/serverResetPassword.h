#ifndef serverResetPassword_H
#define serverResetPassword_H
#include "serverDataStruct.h"

void validReset(int userID ,const char *currentpw,char *newpw, const char *Squestion, const char *Answer ,char *errorMessage);

#endif

