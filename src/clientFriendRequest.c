#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "clientFriendRequest.h"
#include "clientDataStruct.h"
#include "clientHome.h"
#include "clientChat.h"

GtkWidget *button1;
GtkWidget *button2;
GtkWidget *Label;
GtkWidget *Label2;
GtkWidget *Label3;
GtkWidget *Window;
GtkWidget *Fixed;
PangoFontDescription *Font;
PangoFontDescription *Font2;
GtkWidget *VFriendbox;
int tempx[10][3];
GtkWidget *AcceptButton[10];
GtkWidget *DeclineButton[10];	
GtkWidget *AcceptLabel[10];
GtkWidget *Hbox[10];


void delete_event( GtkWidget *widget,gpointer   data ){
    Exit = 1;
}

void goHOME(GtkWidget *widget,gpointer   data ){
	gtk_widget_destroy(Window);
	printHome(NULL,userIDGlobal);
}

#ifndef DEBUG
void printFriendRequests(GtkWidget *widget, int userID){
#endif

#ifdef DEBUG
int main(int argc, char *argv[]){
	gtk_init(&argc,&argv);	
#endif

        GdkColor Color;
        Color.red = 0xffff;
        Color.green = 0x5353;
        Color.blue = 0x5353;
	GtkWidget *title;
	GdkPixbuf *homeBuff;
	GtkWidget *homeIcon;
	GtkWidget *chatHomePageButton;

	
        Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(Window),400,500);
	gtk_widget_modify_bg(Window,GTK_STATE_NORMAL,&Color);       
        g_signal_connect (Window, "delete-event", G_CALLBACK (delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(Window), 70);
        homeBuff  = gdk_pixbuf_new_from_file_at_size("Icons/home.png", 30, 60, NULL);
        homeIcon = gtk_image_new_from_pixbuf (homeBuff);
	gtk_widget_set_size_request(homeIcon, 30, 60);
        chatHomePageButton = gtk_button_new ();
        gtk_button_set_image (GTK_BUTTON (chatHomePageButton), homeIcon);
	title = gtk_image_new_from_file ("Icons/title.png");

       // box1 = gtk_hbox_new (FALSE, 0);
       // gtk_container_add (GTK_CONTAINER (window), box1);

       // button1 = gtk_button_new_with_label("Accept");
       // gtk_widget_set_size_request(button1,50,25);
       // gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);
       // button2 = gtk_button_new_with_label("Decline");
       // gtkvoidvoid_widget_set_size_request(button2,50,25);
       // gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);
       	VFriendbox = gtk_vbox_new(0,14);
	gtk_container_add(GTK_CONTAINER(Window),VFriendbox); 

        //gtk_widget_set_size_request(Label,130,70);
        Label2 = gtk_label_new("Friend Requests");
       // gtk_widget_set_size_request(Label2,150,100);
	gtk_box_pack_start(GTK_BOX(VFriendbox), title, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(VFriendbox), Label2, 0, 0, 0);
	getRequests(userIDGlobal);
        gtk_box_pack_end(GTK_BOX (VFriendbox), chatHomePageButton, FALSE, FALSE, 0 );
	g_signal_connect (chatHomePageButton, "clicked", G_CALLBACK(goHOME), NULL);
	
 	      
//	Label3 = gtk_label_new("Ragui has requested to be your friend");

 /*       Font = pango_font_description_from_string("Serif 15");
        Font2 = pango_font_description_from_string("Serif 15");
        pango_font_description_set_size(Font,30*PANGO_SCALE);
	pango_font_description_set_size(Font2,15*PANGO_SCALE);
        gtk_widget_modify_font(Label,Font);
	gtk_widget_modify_font(Label2,Font2);	
	gtk_widget_modify_font(Label3,Font2);*/

       /* Fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window),Fixed);
        gtk_fixed_put(GTK_FIXED(Fixed),button1, 50,100);     
        gtk_fixed_put(GTK_FIXED(Fixed),button2, 250,100);
        gtk_fixed_put(GTK_FIXED(Fixed),Label, 138,5);
        gtk_fixed_put(GTK_FIXED(Fixed),Label2, 138,40);
        gtk_fixed_put(GTK_FIXED(Fixed),Label3, 50,74);*/
//	g_signal_connect (Window, "Go Home", G_CALLBACK(),NULL);	
	g_signal_connect (Window, "delete-event", G_CALLBACK (delete_event), NULL);
	gtk_widget_show_all(Window);		

        
#ifdef DEBUG
        gtk_main();
	return 0;
#endif
}

#ifndef DEBUG	
////gets if the user accepted or ignored a friend request
////2- call setAnswer
////3- update the gtk window
void getRequests(int userID){
	char userBuff[256], serverBuff[256];
	extern int socketFD;
        extern struct sockaddr_in serverAddress;
	int u = -1, s = -1;

        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0){
                error("ERROR opening socket");
        }
	if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }

	memset(userBuff, 0, sizeof(userBuff));
	sprintf(userBuff,"FRIENDREQUEST getrequests %d",userID);
        u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }
	
	memset(serverBuff, 0, sizeof(serverBuff));
        s = read(socketFD, serverBuff, sizeof(serverBuff));
        if(s < 0){
                 error("Error reading from server.");
        }
        serverBuff[s] = 0;
	
	int requests = 0;
	sscanf(serverBuff, "%*s %d",&requests);

	int fID = -1;
	char fname[25];
	for(int i = 0; i < requests; i++){
		memset(serverBuff, 0, sizeof(serverBuff));
        	u = write(socketFD, "next", strlen("next"));
        	if(u < 0){
        	        error("Error writing to the server.\n");
        	}
        	
		s = read(socketFD, serverBuff, sizeof(serverBuff));
        	if(s < 0){
        	         error("Error reading from server.");
        	}
		printf("RESPONSE: %s\n", serverBuff);
		memset(fname, 0, sizeof(fname));

		sscanf(serverBuff, "%d %s",&fID, fname);
		AcceptLabel[i] = gtk_label_new(fname);
		AcceptButton[i] = gtk_button_new_with_label("Accept");
 		DeclineButton[i] = gtk_button_new_with_label("Decline");
		Hbox[i] = gtk_hbox_new(0,160);
		gtk_box_pack_start(GTK_BOX(Hbox[i]), AcceptLabel[i], 0, 0, 0);
		gtk_box_pack_start(GTK_BOX(Hbox[i]), AcceptButton[i], 0, 0, 0);
		gtk_box_pack_start(GTK_BOX(Hbox[i]), DeclineButton[i], 0, 0, 0);
		gtk_box_pack_start(GTK_BOX(VFriendbox), Hbox[i], 0, 0, 0);	
		tempx[i][0] = userID;
		tempx[i][1] = fID;
		tempx[i][2] = i;
		g_signal_connect(AcceptButton[i], "clicked", G_CALLBACK(acceptRequest), tempx[i]);
		g_signal_connect(DeclineButton[i], "clicked", G_CALLBACK(declineRequest), tempx[i]);				
	}
		
	
}

////sends the answer to the server to update the friends list and requests lists of both users
void acceptRequest(GtkWidget *widget, int data[]){
	char userBuff[256], serverBuff[256];
        extern int socketFD;
        extern struct sockaddr_in serverAddress;
        int u = -1, s = -1;

        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0){
                error("ERROR opening socket");
        }
        if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }

        memset(userBuff, 0, sizeof(userBuff));
        sprintf(userBuff,"FRIENDREQUEST accept %d %d",data[0],data[1]);
        u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }

        memset(serverBuff, 0, sizeof(serverBuff));
        s = read(socketFD, serverBuff, sizeof(serverBuff));
        if(s < 0){
                 error("Error reading from server.");
        }
	gtk_container_remove (GTK_CONTAINER(Hbox[data[2]]), GTK_WIDGET(AcceptButton[data[2]]));
	gtk_container_remove (GTK_CONTAINER(Hbox[data[2]]), GTK_WIDGET(DeclineButton[data[2]]));
	gtk_label_set_text(GTK_LABEL(AcceptLabel[data[2]]), "Friend added");
}

void declineRequest(GtkWidget *widget, int data[]){
        char userBuff[256], serverBuff[256];
        extern int socketFD;
        extern struct sockaddr_in serverAddress;
        int u = -1, s = -1;

        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0){
                error("ERROR opening socket");
        }
        if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }

        memset(userBuff, 0, sizeof(userBuff));
        sprintf(userBuff,"FRIENDREQUEST decline %d %d",data[0],data[1]);
        u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }

        memset(serverBuff, 0, sizeof(serverBuff));
        s = read(socketFD, serverBuff, sizeof(serverBuff));
        if(s < 0){
                 error("Error reading from server.");
        }
	gtk_container_remove (GTK_CONTAINER(Hbox[data[2]]), GTK_WIDGET(AcceptButton[data[2]]));
        gtk_container_remove (GTK_CONTAINER(Hbox[data[2]]), GTK_WIDGET(DeclineButton[data[2]]));
        gtk_label_set_text(GTK_LABEL(AcceptLabel[data[2]]), "Request Deleted");
}

#endif

