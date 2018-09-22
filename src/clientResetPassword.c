#include "clientResetPassword.h"
#include "clientDataStruct.h"
#include "clientSettings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


//prints the gtk page of reset password
GtkWidget *ResetLabel;
GtkWidget *Window;
void destroyWin( GtkWidget *widget,gpointer   data ){
	Exit = 1;
	#ifdef DEBUG
	gtk_main_quit();
	#endif
}


void callSettings(GtkWidget *widget,gpointer   data ){
	#ifdef DEBUG
	printf("Going to Settings");
	gtk_main_quit();
	#endif
	gtk_widget_destroy(Window);
	#ifndef DEBUG
	printSettings(NULL, NULL);
	#endif
}

#ifndef DEBUG
void printResetPassword(GtkWidget *widget,  GtkWidget *list[]){
#endif

#ifdef DEBUG
int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);
#endif

	GtkWidget *Title, *SubmitButton, *ReturnButton, *CurrentPWLabel, *NewPWLabel, *QuestionLabel, *AnswerLabel;
	GtkWidget *ResetVbox, *ResetHbox, *ResetHbox2, *ResetHbox3, *ResetHbox4;
	GdkColor Color;	

	reset *resetdata;	

	Color.red = 0xFFFF;
        Color.green = 0x5353;
        Color.blue = 0x5353;

	resetdata = g_malloc(sizeof(resetdata));
        Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(Window),400,500);
        gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
        gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &Color);
        gtk_container_set_border_width(GTK_CONTAINER(Window), 70);
        gtk_window_set_resizable(GTK_WINDOW(Window), TRUE);
	Title = gtk_image_new_from_file("Icons/title.png");

	ResetVbox = gtk_vbox_new(0,30);
	gtk_container_add(GTK_CONTAINER(Window), ResetVbox);

	resetdata->Entry = gtk_entry_new();
        resetdata->Entry2 = gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(resetdata->Entry),20);
        gtk_entry_set_max_length(GTK_ENTRY(resetdata->Entry2),20);

	ResetLabel = gtk_label_new(" ");
	CurrentPWLabel = gtk_label_new("Enter Current Password:");
	NewPWLabel = gtk_label_new("Enter New Password:");

	ResetHbox = gtk_hbox_new(0,10);
	ResetHbox2 = gtk_hbox_new(0,10);
	
	gtk_box_pack_start(GTK_BOX(ResetHbox), CurrentPWLabel, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(ResetHbox), resetdata->Entry, 1, 1, 0);
	gtk_box_pack_start(GTK_BOX(ResetHbox2), NewPWLabel, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(ResetHbox2), resetdata->Entry2, 1, 1, 0);


	resetdata->Question = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(resetdata->Question),"Where were you born?");
	gtk_combo_box_append_text(GTK_COMBO_BOX(resetdata->Question),"What is your first car?");
	gtk_combo_box_append_text(GTK_COMBO_BOX(resetdata->Question),"What is your favorite animal?");
	gtk_combo_box_append_text(GTK_COMBO_BOX(resetdata->Question),"What is your favorite musician?");
	gtk_combo_box_append_text(GTK_COMBO_BOX(resetdata->Question),"What is your favorite color?");
	
	
	QuestionLabel = gtk_label_new("Please choose a Question:");	
	AnswerLabel = gtk_label_new("Answer:");

	resetdata->Entry3 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(resetdata->Entry3),20);


	SubmitButton = gtk_button_new_with_label("Submit");
	gtk_widget_set_size_request(SubmitButton, 100, 50);			
	ReturnButton = gtk_button_new_with_label("Return to Settings");
        gtk_widget_set_size_request(ReturnButton, 100, 50);
	
	ResetHbox3 = gtk_hbox_new(0,10);
        ResetHbox4 = gtk_hbox_new(0,10);

	gtk_box_pack_start(GTK_BOX(ResetHbox3), QuestionLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(ResetHbox3), resetdata->Question, 1, 1, 0);
        gtk_box_pack_start(GTK_BOX(ResetHbox4), AnswerLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(ResetHbox4), resetdata->Entry3, 1, 1, 0);

	gtk_box_pack_start(GTK_BOX(ResetVbox), Title, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(ResetVbox), ResetHbox, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(ResetVbox), ResetHbox2, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(ResetVbox), ResetHbox3, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(ResetVbox), ResetHbox4, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(ResetVbox), ResetLabel, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(ResetVbox), SubmitButton, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(ResetVbox), ReturnButton, 0, 0, 0);

	g_signal_connect(SubmitButton,"clicked", G_CALLBACK(getResetData), resetdata);
        g_signal_connect(Window,"delete-event",G_CALLBACK(destroyWin),NULL);
	g_signal_connect(ReturnButton,"clicked", G_CALLBACK(callSettings),NULL);


	gtk_widget_show_all(Window);
#ifdef DEBUG
	gtk_main();
#endif
}

void  getResetData(GtkWidget *widget, reset *d){
	const char *currentPW;
	const char *newPW;
        const char *answer;

        currentPW = gtk_entry_get_text(GTK_ENTRY(d->Entry));
        newPW = gtk_entry_get_text(GTK_ENTRY(d->Entry2));
        const int question = gtk_combo_box_get_active(GTK_COMBO_BOX(d->Question));
	answer =  gtk_entry_get_text(GTK_ENTRY(d->Entry3));
        if (!*currentPW){ //checks to see if user inputs nothing
                gtk_label_set_text(GTK_LABEL(ResetLabel),"Current Password field is empty.");
		return;
        }
        if (!*newPW){ //checks to see if user inputs nothing
                gtk_label_set_text(GTK_LABEL(ResetLabel),"New Password field is empty.");
		return;
        }
	 if (question == -1){
		gtk_label_set_text(GTK_LABEL(ResetLabel),"Question field is empty.");
		return;	
        }

	if (!*answer){ //checks to see if user inputs nothing
                gtk_label_set_text(GTK_LABEL(ResetLabel),"Answer field is empty.");
		return;
        }
	if (strlen(newPW)<6 || strlen(newPW)> 25) {
		gtk_label_set_text(GTK_LABEL(ResetLabel), "New Password must be 8-25 characters long");
		return;
	}
	if ((strcmp(newPW, currentPW) == 0) && (strlen(newPW) == strlen(currentPW))){
		 gtk_label_set_text(GTK_LABEL(ResetLabel), "New and Current Password are the same.");
               	 return;
	}	
      //  #ifdef DEBUG
                printf("Current PW is %s. New PW is %s. Question is #%d. Answer is %s.\n", currentPW, newPW, question, answer);
      //  #endif
	#ifndef DEBUG
        validateResetData(currentPW, newPW, question, answer);
	#endif
}

#ifndef DEBUG
void validateResetData(const char *currentPW, const char *newPW, int question, const char *answer){
        char errorMessage[256];
        char userBuff[256];
        char *Squestion;
        switch(question){
                case 0:
                        Squestion = "One";
                        break;
                case 1:
                        Squestion = "Two";
                        break;
                case 2:
                        Squestion = "Three";
                        break;
                case 3:
                        Squestion = "Four";
                        break;
                case 4:
                        Squestion = "Five";
                        break;

        }
        memset(errorMessage, 0, sizeof(errorMessage));
        memset(userBuff, 0, sizeof(userBuff));
        strncat(userBuff, "RESET ", strlen("RESET "));
	sprintf(userBuff,"RESET %d", userIDGlobal);
	//strncat(userBuff, usernameGlobal, strlen(usernameGlobal));
	strncat(userBuff, " ",1);
        strncat(userBuff, currentPW, strlen(currentPW));
        strncat(userBuff, " ",1);
        strncat(userBuff, newPW, strlen(newPW));
        strncat(userBuff, " ",1);
        strncat(userBuff, Squestion, strlen(Squestion));
	strncat(userBuff, " ",1);
	strncat(userBuff, answer, strlen(answer));

        printf("Exit: %d\nThe user buffer: %s\n", Exit, userBuff);

        #ifndef DEBUG
        extern int socketFD;
        extern struct sockaddr_in serverAddress;
        socketFD = socket(AF_INET,SOCK_STREAM,0);
        if(socketFD<0){
                error("Error opening socket");
        }

        if (connect(socketFD,(struct sockaddr*) &serverAddress, sizeof(serverAddress))<0){
                error("Error when connecting to server");
        }

	 int u,s;
        u = write(socketFD, userBuff, strlen(userBuff));
        if(u<0){
                error("Error when writing to the server\n");
        }

        printf("Message sent.\n");
        s = read(socketFD, errorMessage, sizeof(errorMessage)-1);
        if(s<0){
                error("Error when reading from the server.\n");
        }
        errorMessage[s] = 0;
        #endif

        printf("Response: %s\n", errorMessage);

        if(strncmp("RESET OK", errorMessage, strlen("RESET OK")) ==0){
		gtk_label_set_text(GTK_LABEL(ResetLabel), "Reset Password has been successful.");
        }
        else if(strncmp("RESET does not match", errorMessage, strlen("RESET does not match")) == 0){
                gtk_label_set_text(GTK_LABEL(ResetLabel), "Current Password and/or Security Answer is wrong.");
        }
}
#endif




/*//1- gets the username when the button is clicked
//2- call getSecurityQuestion
//3- a- if userFound, calls printQuestion
//   b- else print an error message to the old window
void getUsernameReset(GtkWidget *widget,  GtkWidget *list[]);

//send the username to the server to return the sequrity question and corresponding answer,
//      if the user is found, or an error message if not found
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
void getNewPass(GtkWidget *widget,  GtkWidget *list[]);*/

