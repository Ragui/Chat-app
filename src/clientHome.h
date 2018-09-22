#ifndef clientHome_H
#define clientHome_H

#include <gtk/gtk.h>
#include "clientDataStruct.h"
#include "clientHome.h"

//gets the friends list of the user from the server
//n is the number of friends in the list
//depending on this function,
//	a number of widgets (contacts buttons) will be made and sent to the printHome function


void getNumberFriends(int *fCount, int userID);
void getNumberRequests(int *rCount, int userID);
void getContacts(friend *f, int pos, int userID);

//prints the gtk home page of the user
//list contains the needed widgets
void printHome(GtkWidget *widget,  int userID); 

#endif
