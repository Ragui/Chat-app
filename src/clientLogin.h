#ifndef clientLogin_H
#define clientLogin_H

#include <gtk/gtk.h>
#include "clientHome.h"
#include "clientDataStruct.h"


GtkWidget *Window;

login data;

//prints the gtk design of the login page
void printLogin(GtkWidget *widget,  GtkWidget *list[]);

//1- get the username and password when the login button is pressed
//2- call validateLoginData
//3- a- if it returns -1, reprint the login data with errorMessage
//   b- if returns ID, call the printHome function
void getLoginData(GtkWidget *widget, login *data);


//send the login data to the server and get the answer 
//It returns the user id, or -1 in case of errors 
int validateLoginData(const char *username, const char *password);

void destroy( GtkWidget *widget,gpointer   data );

void callReg(GtkWidget *widget,gpointer   data );

void callRecover(GtkWidget *widget, gpointer data);

#endif 
