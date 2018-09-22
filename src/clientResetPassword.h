#ifndef clientResetPassword_H
#define clientResetPassword_H

#include <gtk/gtk.h>
#include "clientDataStruct.h"


//prints the gtk page of reset password
void printResetPassword(GtkWidget *widget,  GtkWidget *list[]);


void  getResetData(GtkWidget *widget, reset *d);

void validateResetData(const char *currentPW, const char *newPW, int question, const char *answer);

//1- gets the username when the button is clicked
//2- call getSecurityQuestion
//3- a- if userFound, calls printQuestion
//   b- else print an error message to the old window
void getUsernameReset(GtkWidget *widget,  GtkWidget *list[]);

//send the username to the server to return the sequrity question and corresponding answer, 
//	if the user is found, or an error message if not found
//returns userID  if found, -1 otherwise
int getSecurityQuestion(const char *username, char *question, char *correctAnswer);

//prints the sequrity question and input box
void printQuestion(GtkWidget *widget,  GtkWidget *list[]);

//1- get the answer when the button is clicked 
//2- compare it with the correct answer
//3- if correct, call  printNewPass
//   else, print an error message to the old page
void getQuestionAnswer(GtkWidget *widget,  GtkWidget *list[]);

//print the page to reset password
void printNewPass(GtkWidget *widget,  GtkWidget *list[]);

//1- get the new password if the button is clicked 
//2- check if it meets the naming conventions
//3- if valid, send it to server, and print a message
//   if not, print an error message 
void getNewPass(GtkWidget *widget,  GtkWidget *list[]);

#endif
