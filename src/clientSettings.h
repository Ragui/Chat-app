#ifndef clientSettings_H
#define clientSettings_H

#include <gtk/gtk.h>

//gets the settings of the user from the server and put it in the array
void getSettings(int userID, char *data[]);

//1- call getSettings
//2- prints the gtk settings page
void printSettings(GtkWidget *widget,  GtkWidget *list[]);

//returns a string to the font
char *getFont();

//returns an integer to the color
int getColor();

//checks if the password follow the naming conventions
//returns 1 if the password is valid, 0 otherwise
int getPassword(char *errorMessage);

//1- calls getFont
//2- update the font in the gtk page
//3- send the new font to the server
void updateFont(GtkWidget *widget,  GtkWidget *list[]);

//1- calls getColor
//2- update the color in the gtk page
//3- send the new font to the server
void updateColor(GtkWidget *widget,  GtkWidget *list[]);

//1- calls getPassword
//2- if valid ,update the password in the database
//3- print Password updated
void updatePassword(GtkWidget *widget,  GtkWidget *list[]);

#endif
