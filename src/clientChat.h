#ifndef clientChat_H
#define clientChat_H

#include <gtk/gtk.h>
#include "clientDataStruct.h"



void detroyWindow( GtkWidget *widget,gpointer   data);
void goHome(GtkWidget *widget,gpointer   data );
//gets the messages in a chat from the server
void getChat(int user1, int user2);
//void getChat(GtkWidget *b, int user[]);
//1- gets the chatID
//2- calls getChat
//3- prints the chat page with history messages 
void printChat(GtkWidget *widget,  int data[]);

//1- gets the message when the button is clicked 
//2- send the message to the server
//3- print the updated chat
void sendMessage(GtkWidget *widget, int data[]);

//1- when the button is clicked, the corresponding message is deleted 
//2- send the update to the server
//3- prints the updated chat
void deleteMessage(GtkWidget *widget, int messageID);

//1- when the button is clicked, the chat history is deleted
//2- send the update to the server
//3- prints the updated chat
void DeleteAll(GtkWidget *widget, int messageID);

#endif 
