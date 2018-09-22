#ifndef clientFriendRequests_H
#define clientFriendRequests_H

#include <gtk/gtk.h>
#include "clientDataStruct.h"
#include "clientHome.h"

//1- call getFriendRequests
//2- prints the gtk page of the friend requests 
//list contains the needed widgets
void printFriendRequests(GtkWidget *widget,  int userID);

//gets if the user accepted or ignored a friend request
//2- call setAnswer
//3- update the gtk window 
void getRequests(int userID);

//sends the answer to the server to update the friends list and requests lists of both users
void acceptRequest(GtkWidget *widget, int data[]);
void declineRequest(GtkWidget *widget, int data[]);
#endif
