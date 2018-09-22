
#include "clientHome.h"
#include "clientLogin.h"
#include "clientDataStruct.h"
#include "clientChat.h"
#include "clientAddFriend.h"
#include "clientFriendRequest.h"
#include "clientSettings.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include <time.h>



 GtkWidget *logOffBtn, *settingsBtn;
 GtkWidget *title, *requests, *title_and_requests;
 GtkWidget *searchEntry, *searchButton;
 GtkWidget *table;
 GtkWidget *vbox, *hbox1, *hbox2;
 GtkWidget *scrollBox;
 GtkWidget *requestsIcon;
 GtkWidget *addButton, *addFriendIcon;
 GdkColor w_color, b_color, o_color;	//colors for window, buttons, and online contacts
 GtkWidget *messageLabel;
 


int tempF[100][1];
int refresh = 0;

//gets the friends list of the user from the server
//n is the number of friends in the list
//depending on this function,
//      a number of widgets (contacts buttons) will be made and sent to the printHome function


void getNumberRequests(int *rCount, int userID){

    char serverMessage[256];
    memset(serverMessage, 0, sizeof(serverMessage));

	char userBuff[256];
	memset(userBuff, 0, sizeof(userBuff));

	char ID[10];
	memset(userBuff, 0, sizeof(ID));

	sprintf(ID, "%d", userID);
	strncpy(userBuff, "GET REQUESTS FOR ID", strlen("GET REQUESTS FOR ID"));
        strncat(userBuff, " ", 1);
        strncat(userBuff, ID, strlen(ID));
#ifdef DEBUG
	printf("%s\n", userBuff);
#endif

#ifndef DEBUG
	int requests;

    extern int socketFD;
    extern struct sockaddr_in serverAddress;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0){
            error("ERROR opening socket");
    }
     if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
            error("connecting to server failed");
    }
	int u, s;
        u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }
        printf("message sent\n");
        s = read(socketFD, serverMessage, sizeof(serverMessage) - 1);
        if(s < 0){
                 error("Error reading from server.");
        }
        serverMessage[s] = 0;

	printf("Response: %s\n", serverMessage);

        sscanf(serverMessage, "%*s %d", &requests);
#endif
#ifdef DEBUG
	*rCount = 8;
#endif
#ifndef DEBUG
	*rCount = requests;
#endif
}

void getNumberContacts(int *fCount, int userID){


	char serverMessage[256];
    memset(serverMessage, 0, sizeof(serverMessage));

	char userBuff[256];
    memset(userBuff, 0, sizeof(userBuff));

    char ID[10];
    memset(userBuff, 0, sizeof(ID));

    sprintf(ID, "%d", userID);
    strncpy(userBuff, "GET N CONTACTS FOR ID ", strlen("GET N CONTACTS FOR ID "));
    strncat(userBuff, ID, strlen(ID));
#ifdef DEBUG
        printf("%s\n", userBuff);
#endif

#ifndef DEBUG
    int friends;
    extern int socketFD;
    extern struct sockaddr_in serverAddress;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0){
            error("ERROR opening socket");
    }
     if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
            error("connecting to server failed");
    }

    int u, s;
    u = write(socketFD, userBuff, strlen(userBuff));
    if(u < 0){
            error("Error writing to the server.\n");
    }
    printf("message sent\n");
    s = read(socketFD, serverMessage, sizeof(serverMessage) - 1);
    if(s < 0){
             error("Error reading from server.");
    }
    serverMessage[s] = 0;

    printf("Response: %s\n", serverMessage);

    sscanf(serverMessage, "%*s %d", &friends);
#endif
#ifdef DEBUG
    *fCount = 20;
#endif
#ifndef DEBUG
	*fCount = friends;
#endif
}

void getContacts(friend *f ,int pos,  int userID){

	char serverMessage[256];
        memset(serverMessage, 0, sizeof(serverMessage));

        char userBuff[256];
	memset(userBuff, 0, sizeof(userBuff));

	char ID[10];
        memset(ID, 0, sizeof(ID));

	char contactPos[3];
        memset(contactPos, 0, sizeof(contactPos));

	sprintf(ID, "%d", userID);
        sprintf(contactPos, "%d", pos);
	strncpy(userBuff, "GET CONTACT ", strlen("GET CONTACT "));
        strncat(userBuff, contactPos, strlen(contactPos));
        strncat(userBuff, " FOR USER ", strlen(" FOR USER "));
        strncat(userBuff, ID, strlen(ID));
#ifdef DEBUG
        printf("%s\n", userBuff);
#endif

#ifndef DEBUG

    int frID;
    int status;

    char name[25];
    memset(name, 0, sizeof(name));

    extern int socketFD;
    extern struct sockaddr_in serverAddress;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0){
            error("ERROR opening socket");
    }
     if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
            error("connecting to server failed");
    }

    int u, s;
    u = write(socketFD, userBuff, strlen(userBuff));
    if(u < 0){
            error("Error writing to the server.\n");
    }
    printf("message sent\n");
    s = read(socketFD, serverMessage, sizeof(serverMessage) - 1);
    if(s < 0){
             error("Error reading from server.");
    }
    serverMessage[s] = 0;

    printf("Response: %s\n", serverMessage);

    sscanf(serverMessage, "%*s %d %s %d", &frID, name, &status);
#endif

#ifdef DEBUG

    memset(f->username, 0, 26);
    strncpy(f->username ,"Contact", strlen("Contact"));

    if(rand()%2 == 0){
		f->status = 1;
		}
	else{
		f->status = 0;
	}
	f->id = 0;
#endif

#ifndef DEBUG
	memset(f->username, 0, 26);
	strncpy(f->username ,name, strlen(name));
	f->id = frID;
	f->status = status;
#endif


}



void deleteContact(int IDu, int IDf){
#ifndef DEBUG

        char serverMessage[256];
        memset(serverMessage, 0, sizeof(serverMessage));

        char userBuff[256];
        memset(userBuff, 0, sizeof(userBuff));

        char frID[10];
        memset(frID, 0, sizeof(frID));

        char userID[10];
        memset(userID, 0, sizeof(userID));

        sprintf(frID, "%d", IDf);
        sprintf(userID, "%d", IDu);

        strncpy(userBuff, "DELETE CONTACT ", strlen("DELETE CONTACT "));
        strncat(userBuff, frID , strlen(frID));
        strncat(userBuff, " FOR USER ", strlen(" FOR USER "));
        strncat(userBuff, userID, strlen(userID));
#endif

           
#ifdef DEBUG
        printf("Deleting Contact...");
#endif

#ifndef DEBUG

    char name[25];
    memset(name, 0, sizeof(name));

    extern int socketFD;
    extern struct sockaddr_in serverAddress;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0){
            error("ERROR opening socket");
    }
     if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
            error("connecting to server failed");
    }

    int u, s;
    u = write(socketFD, userBuff, strlen(userBuff));
    if(u < 0){
            error("Error writing to the server.\n");
    }
    printf("message sent\n");
    s = read(socketFD, serverMessage, sizeof(serverMessage) - 1);
    if(s < 0){
             error("Error reading from server.");
    }
    serverMessage[s] = 0;

    printf("Response: %s\n", serverMessage);

    //sscanf(serverMessage, "%*s %d %s %d", &frID, name, &status);
#endif



}

#ifndef DEBUG
void deleteCall(GtkWidget* widget, int data[]){
	
	
        int userID = userIDGlobal;
        int friendID = data[0];
        deleteContact(userID, friendID);
        gtk_widget_destroy(Window);
        printHome(NULL,userID);

}
#endif

#ifndef DEBUG
void wDes(GtkWidget *w, gpointer data){
	Exit = 1;
}

void log_Off_Call(GtkWidget* widget, gpointer data){
    gtk_widget_destroy(Window);
    refresh = 1;
	char userBuff[256];
        memset(userBuff, 0, sizeof(userBuff));
        char serverBuff[256];
        memset(serverBuff, 0, sizeof(serverBuff));
        int u = 0, s = 0;
        extern int socketFD;
        extern struct sockaddr_in serverAddress;
        sprintf(userBuff,"LOGOFF %d", userIDGlobal);
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0){
                error("ERROR opening socket");
        }
        if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }

        u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }
        s = read(socketFD, serverBuff, 255);
        if(s < 0){
                error("Error reading from server.");
        }
    printLogin(NULL, NULL);
}

void chat_Call(GtkWidget* widget,int data[]){
	gtk_widget_destroy(Window);
	int x[2];
	x[0] = userIDGlobal;
	x[1] = data[0];
	refresh = 1;
	printChat(NULL,x);
	printf("MYFRIEND  ......   %d\n",data[0]);     
}

void add_Friend_Call(GtkWidget* widget, gpointer data){
    gtk_widget_destroy(Window);
    refresh = 1;
    printAddFriend(NULL, NULL);
}

#endif


#ifndef DEBUG
void settings_Call(GtkWidget* widget, gpointer data){
    gtk_widget_destroy(Window);
    refresh = 1;
    printSettings(NULL, NULL);
}
#endif

#ifndef DEBUG
gboolean refresh_window(void *data){
	if(refresh == 1){
		return FALSE;
	}
       	gtk_widget_destroy(Window);	
	printHome(NULL,userIDGlobal);	
	return TRUE;
}
#endif
//prints the gtk home page of the user
//list contains the needed widgets

#ifdef DEBUG

static void search_Contact(GtkWidget* widget, gpointer data){
   g_print("Searching %s\n", gtk_entry_get_text(GTK_ENTRY(data)));
}

static void chat_Call(GtkWidget* widget, gpointer data){
   g_print("Searching %s\n", gtk_entry_get_text(GTK_ENTRY(data)));
}

static void settings_Call(GtkWidget* widget, gpointer data){
    g_print("Going to settings page...\n");
}

static void add_Friend_Call(GtkWidget* widget, gpointer data){
    g_print("Going to requests page...\n");
}

static void deleteCall(GtkWidget* widget, gpointer data){
    g_print("deleting contact....\n");
}


#endif

//prints the gtk home page of the user

////list contains the needed widgets
#ifndef DEBUG
void printHome(GtkWidget *widget, int userID){
#endif

#ifdef DEBUG
int main(int argc, char *argv[]){
	int userID = 0;
	gtk_init(&argc, &argv);
#endif

  int num_Contacts = 0;
  int num_Requests = 0;
  int i;
  refresh = 0;
 	    
  //bool found = false;
  //const char *notFound = "Contact not found";

  getNumberContacts(&num_Contacts, userID);
  getNumberRequests(&num_Requests, userID);

  friend fr[num_Contacts];
  GtkWidget *button[num_Contacts];
  GtkWidget *deleteButton[num_Contacts];
  GtkWidget *hbox3[num_Contacts];  
  
  for (i = 0; i < num_Contacts; i++){
 	 getContacts(&fr[i], i, userID);
	 
  }
  w_color.red = 0xFFFF;
  w_color.green = 0x5353;
  w_color.blue = 0x5353;

  b_color.red = 0xFFFF;
  b_color.green = 0x9353;
  b_color.blue = 0x9353;

  o_color.red = 0x9353;
  o_color.green = 0xFFFF;
  o_color.blue = 0x9353;

  Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);       //create Window
  gtk_widget_set_size_request(Window, 400, 500);      //size Window
  gtk_window_set_title(GTK_WINDOW(Window), "ChatBot");    //title window
  gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
  gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &w_color);  //change color
#ifndef DEBUG
  g_signal_connect(Window,"delete-event",G_CALLBACK(wDes),NULL); //close
#endif
  title = gtk_image_new_from_file("Icons/title.png");           //window title
  gtk_container_set_border_width(GTK_CONTAINER(Window), 20); //border

  searchEntry = gtk_entry_new();             //search contact textbox
  gtk_widget_set_size_request(searchEntry, 300, 30); //change size textbox
  searchButton = gtk_button_new_with_label("Search");  //search button
#ifdef DEBUG
  g_signal_connect(searchButton,"clicked",G_CALLBACK(search_Contact), searchEntry); //search by clicking
  g_signal_connect(searchEntry,"activate",G_CALLBACK(search_Contact), searchEntry); //search by pressing enter
#endif 
 //if(found == FALSE){
    messageLabel = gtk_label_new(NULL);
  //}
  //else{
   // messageLabel = gtk_button_new();
  //}
  requests = gtk_button_new();  //friend requests button
  gtk_widget_set_size_request(requests,70,50);   //change size

  switch(num_Requests){   //icon friend requests based on number of requests
        case 1 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests1.png", 350, 60,NULL));
                 break;
        case 2 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests2.png", 350, 60,NULL));
                 break;
        case 3 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests3.png", 350, 60,NULL));
                 break;
        case 4 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests4.png", 350, 60,NULL));
                 break;
        case 5 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests5.png", 350, 60,NULL));
                 break;
        case 6 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests6.png", 350, 60,NULL));
                 break;
        case 7 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests7.png", 350, 60,NULL));
                 break;
        case 8 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests8.png", 350, 60,NULL));
                 break;
        case 9 : requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests9.png", 350, 60,NULL));
                 break;
        default: requestsIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/friendRequests.png", 350, 60,NULL));

  }
  gtk_widget_set_size_request(requestsIcon,70,50); //change size icon
  gtk_button_set_image (GTK_BUTTON (requests), requestsIcon);  //attach icon to button
  gtk_widget_modify_bg( GTK_WIDGET(requests), GTK_STATE_NORMAL, &w_color); //change color button
#ifndef DEBUG
  g_signal_connect(requests,"clicked",G_CALLBACK(printFriendRequests),NULL);  //call function to open friend requests page
#endif
  title_and_requests = gtk_hbox_new(FALSE, 10);   //box for title and requests
  gtk_container_add(GTK_CONTAINER(title_and_requests), title);
  gtk_container_add(GTK_CONTAINER(title_and_requests), requests);  //items added to box
  if(num_Requests == 0){
    gtk_container_remove(GTK_CONTAINER(title_and_requests),requests); //if no friend requests remove button
  }
  hbox1=gtk_hbox_new(FALSE, 0);  //box for search items
  gtk_container_add(GTK_CONTAINER(hbox1), searchEntry);
  gtk_container_add(GTK_CONTAINER(hbox1), searchButton); //items added


  for(i=0;i<num_Contacts;i++){ //create list of contactsi
      hbox3[i]=gtk_hbox_new(FALSE, 0);
      button[i] = gtk_button_new_with_label(fr[i].username);     //button for each contact
      deleteButton[i] = gtk_button_new_with_label("X");
      gtk_widget_set_size_request(button[i], 290, 30);  //size buttons
      gtk_widget_set_size_request(deleteButton[i], 30, 30);  //size buttons
      
      if(fr[i].status == 0){
      		gtk_widget_modify_bg(GTK_WIDGET(button[i]), GTK_STATE_NORMAL, &b_color); //change color based on status
      }
      else{
		gtk_widget_modify_bg(GTK_WIDGET(button[i]), GTK_STATE_NORMAL, &o_color);
      }
     tempF[i][0] = fr[i].id;
     gtk_container_add(GTK_CONTAINER(hbox3[i]), button[i]);
     gtk_container_add(GTK_CONTAINER(hbox3[i]), deleteButton[i]);
     g_signal_connect(button[i],"clicked",G_CALLBACK(chat_Call), tempF[i]);  //call function that opens chat
     g_signal_connect(deleteButton[i],"clicked",G_CALLBACK(deleteCall),tempF[i]);
  }

  table = gtk_table_new(num_Contacts, 1, TRUE);  //table to display contacts
  gtk_table_set_row_spacings (GTK_TABLE (table), 0);
  gtk_table_set_col_spacings (GTK_TABLE (table), 0);

  for(i=0;i<num_Contacts;i++){   //add contacts to table
      gtk_table_attach(GTK_TABLE (table), hbox3[i],0,1,i, i+1,GTK_FILL,GTK_FILL,0,0);
  }

  scrollBox = gtk_scrolled_window_new(NULL,NULL);  //add scroll option to table
  gtk_widget_set_size_request(scrollBox, 340, 300);
  gtk_widget_modify_bg(GTK_WIDGET(scrollBox), GTK_STATE_NORMAL, &w_color);
  gtk_container_set_border_width (GTK_CONTAINER (scrollBox), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollBox),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollBox),table);

  hbox2 = gtk_hbox_new(FALSE, 40);   //box for lower elements
  settingsBtn = gtk_button_new_with_label("Settings"); //settings button
  gtk_widget_set_size_request(settingsBtn, 60, 50);
//#ifdef DEBUG 
  g_signal_connect(settingsBtn,"clicked",G_CALLBACK(settings_Call), NULL);  //call function to open settings
//#endif
  gtk_container_add(GTK_CONTAINER(hbox2), settingsBtn);  //add button to box
  logOffBtn = gtk_button_new_with_label("Log Off");    //log off button
  gtk_widget_set_size_request(logOffBtn, 100, 50);
#ifndef DEBUG
  g_signal_connect(logOffBtn,"clicked",G_CALLBACK(log_Off_Call), NULL);  //call function to log off
#endif
  gtk_container_add(GTK_CONTAINER(hbox2), logOffBtn);  //add button to box
  addButton = gtk_button_new();           //add friend button
  addFriendIcon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size("Icons/addFriend.png", 60, 50,NULL));  //add friend icon
  gtk_widget_set_size_request(addFriendIcon,60,50);
  gtk_button_set_image (GTK_BUTTON (addButton), addFriendIcon);  //attach icon to button
  gtk_widget_modify_bg( GTK_WIDGET(addButton), GTK_STATE_NORMAL, &w_color);

  g_signal_connect(addButton,"clicked",G_CALLBACK(add_Friend_Call), NULL);   //call function to open add friends page

  gtk_container_add(GTK_CONTAINER(hbox2), addButton);   //add button to box


  vbox = gtk_vbox_new(FALSE, 5);   //vertical box through the Window
  gtk_box_pack_start(GTK_BOX(vbox), title_and_requests, 1,0,0);
  //gtk_box_pack_start(GTK_BOX(vbox), hbox1, 1,0,0);
  gtk_box_pack_start(GTK_BOX(vbox), messageLabel, 1,0,0);
  gtk_box_pack_start(GTK_BOX(vbox), scrollBox, 1,0,0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox2, 1,0,0);  //all elements added to vertical box

  gtk_container_add(GTK_CONTAINER(Window), vbox);
  gtk_widget_show_all(Window);

#ifndef DEBUG  
  g_timeout_add_seconds(300, refresh_window ,NULL);
#endif

 
	
#ifdef DEBUG
 gtk_main();
 return 0;
}
#endif
#ifndef DEBUG
}
#endif

