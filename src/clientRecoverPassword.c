#include "clientRecoverPassword.h"
#include "clientDataStruct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "clientLogin.h"

GtkWidget *RecoverLabel;
GtkWidget *Window;


void destroyWIN( GtkWidget *widget, gpointer data ){
	Exit = 1;
	#ifdef DEBUG
	gtk_main_quit();
	#endif
}

void callLogin(GtkWidget *widget, gpointer data){
	#ifdef DEBUG
	printf("Going to Login\n");
	gtk_main_quit();
	#endif
	gtk_widget_destroy(Window);
	#ifndef DEBUG
        printLogin(NULL, NULL);
	#endif

}


#ifndef DEBUG
void printRecoverPassword(GtkWidget *widget,  GtkWidget *list[]){
#endif


#ifdef DEBUG
int main(int argc, char *argv[]){
        gtk_init(&argc, &argv);
#endif

        GtkWidget *Title, *SubmitButton, *UsernameLabel,  *QuestionLabel, *AnswerLabel, *ReturnButton;
        GtkWidget *RecoverVbox, *RecoverHbox, *RecoverHbox2, *RecoverHbox3;
	GdkColor Color;

        recover *recoverdata;

        Color.red = 0xFFFF;
        Color.green = 0x5353;
        Color.blue = 0x5353;

        recoverdata = g_malloc(sizeof(recoverdata));
        Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(Window),400,500);
        gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
        gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &Color);
        gtk_container_set_border_width(GTK_CONTAINER(Window), 60);
        gtk_window_set_resizable(GTK_WINDOW(Window), TRUE);
        Title = gtk_image_new_from_file("Icons/title.png");

        RecoverVbox = gtk_vbox_new(0,30);
        gtk_container_add(GTK_CONTAINER(Window), RecoverVbox);

        recoverdata->Entry = gtk_entry_new();
        recoverdata->Entry2 = gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(recoverdata->Entry),20);
        gtk_entry_set_max_length(GTK_ENTRY(recoverdata->Entry2),20);

        RecoverLabel = gtk_label_new(NULL);
        UsernameLabel = gtk_label_new("Enter Username:");
        QuestionLabel = gtk_label_new("Please choose a Question:");
        AnswerLabel = gtk_label_new("Answer:");

        RecoverHbox = gtk_hbox_new(0,10);
        RecoverHbox2 = gtk_hbox_new(0,10);
        RecoverHbox3 = gtk_hbox_new(0,10);

        recoverdata->Question = gtk_combo_box_new_text();
        gtk_combo_box_append_text(GTK_COMBO_BOX(recoverdata->Question),"Where were you born?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(recoverdata->Question),"What is your first car?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(recoverdata->Question),"What is your favorite animal?");
	gtk_combo_box_append_text(GTK_COMBO_BOX(recoverdata->Question),"What is your favorite musician?");
        gtk_combo_box_append_text(GTK_COMBO_BOX(recoverdata->Question),"What is your favorite color?");


        gtk_box_pack_start(GTK_BOX(RecoverHbox), UsernameLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverHbox), recoverdata->Entry, 1, 1, 0);
        gtk_box_pack_start(GTK_BOX(RecoverHbox2), QuestionLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverHbox2), recoverdata->Question, 1, 1, 0);
        gtk_box_pack_start(GTK_BOX(RecoverHbox3), AnswerLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverHbox3), recoverdata->Entry2, 1, 1, 0);

        SubmitButton = gtk_button_new_with_label("Submit");
        gtk_widget_set_size_request(SubmitButton, 80, 60);
	ReturnButton = gtk_button_new_with_label("Return to Login");
        gtk_widget_set_size_request(ReturnButton, 80, 60);

        gtk_box_pack_start(GTK_BOX(RecoverVbox), Title, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverVbox), RecoverHbox, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverVbox), RecoverHbox2, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverVbox), RecoverHbox3, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverVbox), RecoverLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(RecoverVbox), SubmitButton, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(RecoverVbox), ReturnButton, 0, 0, 0);

	g_signal_connect(ReturnButton,"clicked", G_CALLBACK(callLogin),NULL);
        g_signal_connect(SubmitButton,"clicked", G_CALLBACK(getRecoverData),recoverdata);
        g_signal_connect(Window,"delete-event",G_CALLBACK(destroyWIN),NULL);


        gtk_widget_show_all(Window);
        #ifdef DEBUG
        gtk_main();
        #endif
}
void  getRecoverData(GtkWidget *widget, recover *d){
        const char *username;
        const char *answer;
        char *RecoverMessage = g_malloc(256);
	char *password = "\0";

        username = gtk_entry_get_text(GTK_ENTRY(d->Entry));
        answer = gtk_entry_get_text(GTK_ENTRY(d->Entry2));
        const int question = gtk_combo_box_get_active(GTK_COMBO_BOX(d->Question));
	if (!*username){ //checks to see if user inputs nothing
                gtk_label_set_text(GTK_LABEL(RecoverLabel),"Username field is empty.");
                return;
        }
        if (question == -1){ //checks to see if user inputs nothing
                gtk_label_set_text(GTK_LABEL(RecoverLabel),"Question field is empty.");
                return;
        }
        if (!*answer){ //checks to see if user inputs nothing
                gtk_label_set_text(GTK_LABEL(RecoverLabel),"Answer field is empty.");
                return;
        }
        #ifdef DEBUG
                printf("Username is %s. Answer is %s. Question is #%d\n", username, answer, question);
        #endif
	#ifndef DEBUG
        password = validateRecoverData(username, answer, question, password);
	#endif
       // #ifdef DEBUG
               printf("User password is %s\n", password);
       //#endif
        if(strcmp(password, "\0") != 0){
                 sprintf(RecoverMessage, "Your Password is %s", password);
                 gtk_label_set_text(GTK_LABEL(RecoverLabel), RecoverMessage);
        }
}

#ifndef DEBUG
char *validateRecoverData(const char *username, const char *answer, int question, char *password){
        char errorMessage[256];
        char userBuff[256];
       // char *Squestion;
        password = (char *)g_malloc(256);

   /*     switch(question){
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
	}*/
        memset(errorMessage, 0, sizeof(errorMessage));
        memset(userBuff, 0, sizeof(userBuff));
	sprintf(userBuff,"RECOVER %s %d %s", username, question+1, answer);
	/*
        strncat(userBuff, "RECOVER ", strlen("RECOVER "));
        strncat(userBuff, username, strlen(username));
        strncat(userBuff, " ",1);
        strncat(userBuff, Squestion, strlen(Squestion));
        strncat(userBuff, " ",1);
        strncat(userBuff, answer, strlen(answer));*/

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

        if(strncmp("RECOVER OK", errorMessage, strlen("RECOVER OK")) ==0){
                sscanf(errorMessage,"%*s %*s %s", password);
        }
        else if(strncmp("RECOVER does not match", errorMessage, strlen("RECOVER does not match")) == 0){
                gtk_label_set_text(GTK_LABEL(RecoverLabel), "Answer to the Security Question is wrong.");
                password = "\0";
        }
        else if(strncmp("RECOVER not found", errorMessage, strlen("RECOVER not found")) == 0){
                gtk_label_set_text(GTK_LABEL(RecoverLabel), "Username not found.");
		password = "\0";
	}
        return(password);
}
#endif
