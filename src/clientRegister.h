#ifndef clientRegister_H
#define clientRegister_H

#include <gtk/gtk.h>
#include "clientHome.h"




registration data2;


//prints the gtk register page
void printRegister(GtkWidget *widget,  GtkWidget *list[]);

//1- get the input data when the register button is clicked 
//2- call validateRegisterData
//3- a- if valid, call printHome
//   b- if not, add an error message to the old registerPage
void getRegisterData(GtkWidget *widget, registration *data);

//checks the naming conventions of each input.
//If valid, it sends the data to the server to save it in the database
//int returns the user id or -1 in case of error
int validateRegisterData(const char *fName, const char *lName, const char *uName, const char *email,const char *password, const int question, const char *answer);

//this function initializes the window title, size, color, border width
//void initialize_window(GtkWidget *window);

void initialize_window(GtkWidget *window);

void on_changed(GtkComboBox *widget, registration *data);

GtkWidget *makeEntry(GtkWidget *lName, GtkWidget *fName, GtkWidget *email, GtkWidget *userName,
		     GtkWidget *password, registration *data);


//GtkWidget *makeComboBox();


#endif
