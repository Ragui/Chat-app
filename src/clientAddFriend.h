#ifndef clientAddFriend_H
#define clientAddFriend_H

#include "clientDataStruct.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>


GtkWidget *SearchButton, *AddButton;
GtkWidget *SearchLabel, *AddFriendMessageLabel;
GtkWidget *AddFixed;
GdkColor Color;

typedef struct add_data{
        GtkWidget *Entry;       //friend input for username
} add;

//prints the add friend page
void printAddFriend(GtkWidget *widget,  GtkWidget *list[]);

//when the user enters the username and click search, this function will be called
//1- will send the username to the server (can be get from the search entry)
//2- get the answer (found or not)
//3-a- If found, it should print the friend's name and an add button
//  b. if not found, should print the search entry and button (old window) + a warning message
void getAddFriendData(GtkWidget *widget, add *data);

//send the username to the server
//returns the id of the user if found, -1 otherwise
int searchFriend(const char *f);

//If the users clicks add 
//it will send the friendID to the server to send friend request, if the user choose to add him
//prints "friend added"
void addFriend(GtkWidget *widget, login *data);

#endif
