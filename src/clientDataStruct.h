#ifndef clientDataStruct_H
#define clientDataStruct_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_BORDER 30
#define TITLE_SIZE 50
#define PAGE_DESC_SIZE 24



typedef struct login_data{
        GtkWidget *Entry;       //user input for username
        GtkWidget *Entry2;      //user input for password
} login;

typedef enum b{
        true = 1,
        false = 0
}bool;

typedef struct reset_data{
        GtkWidget *Entry;       //user input for current password
        GtkWidget *Entry2;      //user input for new password
	GtkWidget *Question;
        GtkWidget *Entry3;	//user input fo security answer
} reset;

typedef struct recover_data{
        GtkWidget *Entry;       //user input for username
        GtkWidget *Question;
        GtkWidget *Entry2;      //user input for security answer
} recover;


typedef struct register_data
{
        GtkWidget *lName;	//user input for last name
        GtkWidget *fName;	//user input for firt name
        GtkWidget *email;	//user input for email adddress
        GtkWidget *userName;	//user input for user name
        GtkWidget *password;	//user input for password
        GtkWidget  *question;	//user input for question
        GtkWidget *answer;	//user input for answer
}registration;

typedef struct Friend{
	int id;
	char username[26];
	int status; //online or offline
}friend;

typedef struct m{
	int senderID;
	char *text;
	int messageID;
}message;

typedef struct Chat{
//        account users[2];
        int users[2];
        message *history;       //dynamic array for chat history
        int length;
}chat;

//int exit = 0;
int Exit;
int userIDGlobal;
char *usernameGlobal;
void error(const char *msg);

#endif
