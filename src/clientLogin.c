#include "clientLogin.h"
#include "clientHome.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "clientRegister.h"
#include "clientRecoverPassword.h"

GtkWidget *LoginMessageLabel;

void destroy( GtkWidget *widget,gpointer   data ){
    Exit = 1;
}

void callReg(GtkWidget *widget,gpointer   data ){
	gtk_widget_destroy(Window);
	printRegister(NULL, NULL);	
}

void callRecover(GtkWidget *widget, gpointer data){
	gtk_widget_destroy(Window);
	printRecoverPassword(NULL, NULL);
}

void printLogin(GtkWidget *widget,  GtkWidget *list[]){
	
	GtkWidget *LoginButton,*ForgotPWButton, *NewUserButton;
	GtkWidget *UsernameLabel;
	GtkWidget *PasswordLabel;
//	GtkWidget *LoginFixed;
	GtkWidget *VLoginBox, *HLoginBox, *HLoginBox2, *VLoginBox2;
	GtkWidget *Title;
	GdkColor Color;
	extern login data;

	Color.red = 0xFFFF;
	Color.green = 0x5353;
	Color.blue = 0x5353;

	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(Window),400,500);
	gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
	gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &Color);
	gtk_container_set_border_width(GTK_CONTAINER(Window), 90);	
	gtk_window_set_resizable(GTK_WINDOW(Window), TRUE);

	Title = gtk_image_new_from_file("Icons/title.png");  

//	Title = gtk_image_new_from_file("Icons/title.png");	

	LoginButton = gtk_button_new_with_label("Log-in"); 
	gtk_widget_set_size_request(LoginButton, 140, 50);
	ForgotPWButton = gtk_button_new_with_label("Forgot Password?");
	gtk_widget_set_size_request(ForgotPWButton, 140, 50);
	NewUserButton = gtk_button_new_with_label("New User");
	gtk_widget_set_size_request(NewUserButton, 140, 50);
	  	

	data.Entry = gtk_entry_new();
	data.Entry2 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(data.Entry),20);
	gtk_entry_set_max_length(GTK_ENTRY(data.Entry2),20);

	LoginMessageLabel = gtk_label_new(NULL);
        UsernameLabel = gtk_label_new("Username");
        PasswordLabel = gtk_label_new("Password");


	VLoginBox = gtk_vbox_new(0,30);

	gtk_box_pack_start(GTK_BOX(VLoginBox), LoginMessageLabel, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(VLoginBox), LoginButton, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(VLoginBox), ForgotPWButton, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(VLoginBox), NewUserButton, 0, 0, 0);


	HLoginBox = gtk_hbox_new(0,0);
	HLoginBox2 = gtk_hbox_new(0,0);
	
	gtk_box_pack_start(GTK_BOX(HLoginBox), UsernameLabel, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(HLoginBox), data.Entry, 1, 1, 0);

	gtk_box_pack_start(GTK_BOX(HLoginBox2), PasswordLabel, 0, 0, 0);
  	gtk_box_pack_start(GTK_BOX(HLoginBox2), data.Entry2, 1, 1, 0);

	VLoginBox2 = gtk_vbox_new(0,20);

	gtk_container_add(GTK_CONTAINER(Window), VLoginBox2);

	gtk_box_pack_start(GTK_BOX(VLoginBox2), Title, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(VLoginBox2), HLoginBox, 1, 1, 0);
	gtk_box_pack_start(GTK_BOX(VLoginBox2), HLoginBox2, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(VLoginBox2), VLoginBox, 0, 0, 0);

	g_signal_connect(LoginButton,"clicked", G_CALLBACK(getLoginData),&data);
        g_signal_connect(Window,"delete-event",G_CALLBACK(destroy),NULL);

//	LoginFixed = gtk_fixed_new();

//	gtk_container_add(GTK_CONTAINER(Window), LoginFixed);

/*	gtk_fixed_put(GTK_FIXED(LoginFixed),LoginButton, 135, 300);
	gtk_fixed_put(GTK_FIXED(LoginFixed), ForgotPWButton, 135, 370);
	gtk_fixed_put(GTK_FIXED(LoginFixed), NewUserButton, 135, 440);
	gtk_fixed_put(GTK_FIXED(LoginFixed), data->Entry, 130, 100);
	gtk_fixed_put(GTK_FIXED(LoginFixed), data->Entry2, 130, 140);
	gtk_fixed_put(GTK_FIXED(LoginFixed), LoginMessageLabel, 120, 170);
	gtk_fixed_put(GTK_FIXED(LoginFixed), UsernameLabel, 70, 105);
	gtk_fixed_put(GTK_FIXED(LoginFixed), PasswordLabel, 75, 145);

	gtk_fixed_put(GTK_FIXED(LoginFixed), Title, 145, 30);	*/

	
	gtk_entry_set_visibility(GTK_ENTRY(data.Entry2), FALSE);

	g_signal_connect(GTK_OBJECT(ForgotPWButton), "clicked", G_CALLBACK(callRecover),NULL);
	g_signal_connect(GTK_OBJECT(NewUserButton), "clicked", G_CALLBACK(callReg),NULL );
	gtk_widget_show_all(Window);
}


//1- get the username and password when the login button is pressed
//2- call validateLoginData
//3- a- if it returns -1, reprint the login data with errorMessage
//   b- if returns ID, call the printHome function
void  getLoginData(GtkWidget *widget, login *d){
	const char *username;
	const char *password;
	int id = -1;

	username = gtk_entry_get_text(GTK_ENTRY(d->Entry));
	password = gtk_entry_get_text(GTK_ENTRY(d->Entry2));

	if (!*username){ //checks to see if user inputs nothing 
		gtk_label_set_text(GTK_LABEL(LoginMessageLabel),"Username field is empty.");
	}
	if (!*password){ //checks to see if user inputs nothing
		gtk_label_set_text(GTK_LABEL(LoginMessageLabel),"Password field is empty.");
	}
	#ifdef DEBUG
		printf("Username is %s. Password is %s\n", username, password);
	#endif
	
	id = validateLoginData(username, password);
	#ifdef DEBUG
		printf("User ID is %d\n", id);
	#endif
	if(id != -1){
		usernameGlobal = malloc(sizeof(char) * (strlen(username) +1) );
		strncpy(usernameGlobal, username, strlen(username));
		gtk_widget_destroy(Window);
		printHome(NULL, id);
	}
	userIDGlobal =  id;
}

//send the login data to the server and get the answer
//It returns the user id, or -1 in case of error
int  validateLoginData(const char *username, const char *password){
	int id = -1;
	char errorMessage[256];
	memset(errorMessage, 0, sizeof(errorMessage));	
	#ifdef DEBUG
//		errorMessage = "Username and Password is incorrect.";
	#endif
	char userBuff[256];
	memset(userBuff, 0, sizeof(userBuff));
	strncpy(userBuff, "LOGIN ", strlen("LOGIN "));
	strncat(userBuff, username, strlen(username));
	strncat(userBuff, " ", 1);
	strncat(userBuff, password, strlen(password));
	
	printf("Exit: %d\nThe user buffer: %s\n",Exit, userBuff);

#ifndef DEBUG
	extern int socketFD;
	extern struct sockaddr_in serverAddress;	
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0){
                error("ERROR opening socket");
        }
        //conect to server
        if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }
        
	int u, s;
	u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }
        printf("message sent\n");
        s = read(socketFD, errorMessage, sizeof(errorMessage) - 1);
        if(s < 0){
                 error("Error reading from server.");
        }
        errorMessage[s] = 0;
#endif	
	printf("Response: %s\n", errorMessage);


	if(strncmp("LOGIN OK", errorMessage, strlen("LOGIN OK")) == 0){
		sscanf(errorMessage, "%*s %*s %d", &id);
	}
	else if(strncmp("LOGIN does not match", errorMessage, strlen("LOGIN does not match")) == 0){
		gtk_label_set_text(GTK_LABEL(LoginMessageLabel), "Username and password does not match.");
	}
	else if(strncmp("LOGIN not found", errorMessage, strlen("LOGIN not found")) == 0){
                gtk_label_set_text(GTK_LABEL(LoginMessageLabel), "Username not found.");
        }
	return(id);
}


#ifdef DEBUG
int main(int argc, char *argv[]){

	gtk_init(&argc, &argv);
	printLogin(NULL, NULL);
//	g_signal_connect(GTK_OBJECT(LoginButton),"clicked", G_CALLBACK(getLoginData),&data);
	g_signal_connect(Window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();

	return -1;
}
#endif
