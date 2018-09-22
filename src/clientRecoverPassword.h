#ifndef clientRecoverPassword_H
#define clientRecoverPassword_H

#include <gtk/gtk.h>
#include "clientDataStruct.h"





void printRecoverPassword(GtkWidget *widget,  GtkWidget *list[]);

void  getRecoverData(GtkWidget *widget, recover *d);

char *validateRecoverData(const char *username, const char *answer, int question, char *password);

#endif
