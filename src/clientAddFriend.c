#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clientAddFriend.h"
#include "clientDataStruct.h"
#include "clientHome.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int friend_id;
GtkWidget *Window;

void goH(GtkWidget *widget,gpointer   data ){
        gtk_widget_destroy(Window);
        printHome(NULL, userIDGlobal);
}

void closePage( GtkWidget *widget,gpointer   data ){
 
    Exit = 1;
} 


//prints the add friend page
#ifndef DEBUG
void printAddFriend( GtkWidget *widget,  GtkWidget *list[]){
#endif
#ifdef DEBUG
int main(int argc, char *argv[]){
#endif
	GtkWidget * homeIcon, *titleIcon, *chatHomePageButton, *Box3, *Box1, *Box2;
	GdkPixbuf *homeBuff, *titleBuff;


	add *data;
	data = g_malloc(sizeof(data));

        Color.red = 0xFFFF;
        Color.green = 0x5353;
        Color.blue = 0x5353;

        #ifdef DEBUG
        gtk_init(&argc, &argv);
        #endif

	Window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(Window),400,500);
        gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
        gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &Color);

	Box3       = gtk_hbox_new(FALSE, 0);
	Box2       = gtk_hbox_new(FALSE, 0);
	Box1       = gtk_vbox_new(FALSE, 0);

	titleBuff = gdk_pixbuf_new_from_file_at_size("Icons/title.png", 350, 60,NULL);
        homeBuff  = gdk_pixbuf_new_from_file_at_size("Icons/home.png", 30, 60, NULL);

        homeIcon = gtk_image_new_from_pixbuf (homeBuff);
        titleIcon = gtk_image_new_from_pixbuf (titleBuff);
        gtk_widget_set_size_request(titleIcon, 350, 70);
        gtk_widget_set_size_request(homeIcon, 30, 60);
        chatHomePageButton = gtk_button_new ();
        gtk_button_set_image (GTK_BUTTON (chatHomePageButton), homeIcon);
	gtk_box_pack_end(GTK_BOX (Box3), titleIcon, FALSE, FALSE, 0 );
        gtk_box_pack_end(GTK_BOX (Box3), chatHomePageButton, FALSE, FALSE, 0 );

	SearchButton = gtk_button_new_with_label("Search");
	gtk_widget_set_size_request(SearchButton, 100, 40);
	gtk_widget_set_size_request(Box3, 380, 100);
	gtk_widget_set_size_request(Box2, 380, 400);
	AddButton = gtk_button_new_with_label("+");
        gtk_widget_set_size_request(AddButton, 25, 25);
	
	data->Entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(data->Entry),20);
	
	SearchLabel = gtk_label_new("Friend's Username");
	AddFriendMessageLabel = gtk_label_new(NULL);
	
	AddFixed = gtk_fixed_new();

	gtk_container_add(GTK_CONTAINER(Window), Box1);	
	gtk_container_add(GTK_CONTAINER(Box2), AddFixed);
	gtk_box_pack_end(GTK_BOX (Box1), Box2,FALSE, FALSE, 0 );
	gtk_box_pack_end(GTK_BOX (Box1), Box3,FALSE, FALSE, 0 ) ;
	gtk_widget_set_size_request(Box3, 400, 50);	
	gtk_fixed_put(GTK_FIXED(AddFixed), SearchButton, 235, 50);
	gtk_fixed_put(GTK_FIXED(AddFixed), AddButton, 272, 120);
	gtk_fixed_put(GTK_FIXED(AddFixed), AddFriendMessageLabel, 60, 120);
	gtk_fixed_put(GTK_FIXED(AddFixed), data->Entry, 60, 55);

        g_signal_connect(GTK_OBJECT(SearchButton),"clicked", G_CALLBACK(getAddFriendData),data);
        g_signal_connect(GTK_OBJECT(AddButton),"clicked", G_CALLBACK(addFriend),data);
        g_signal_connect(Window,"delete-event",G_CALLBACK(closePage),NULL);
	g_signal_connect(chatHomePageButton,"clicked",G_CALLBACK(goH),data);	

	gtk_widget_show_all(Window);
	gtk_widget_hide(AddButton);

#ifdef DEBUG
return 0;
#endif
}

//when the user enters the username and click search, this function will be called
//1- will send the username to the server (can be get from the search entry)
//2- get the answer (found or not)
//3-a- If found, it should print the friend's name and an add button
//  b. if not found, should print the search entry and button (old window) + a warning message
void getAddFriendData(GtkWidget *widget, add *data){
	const char *search_id;
	int id;

	search_id = gtk_entry_get_text(GTK_ENTRY(data->Entry));

        if (!*search_id){ //checks to see if user inputs nothing 
                gtk_label_set_text(GTK_LABEL(AddFriendMessageLabel),"Friend's Username was not entered.");
                return;
        }

	#ifdef DEBUG
        printf("Friend's Username is %s.\n", search_id);
        #endif

	id = searchFriend(search_id);

        #ifdef DEBUG
        printf("Answer from server is %d. \n", id);
        #endif

	if(id != -1){
	gtk_label_set_text(GTK_LABEL(AddFriendMessageLabel), search_id);
	gtk_widget_show(AddButton);
	friend_id = id;
	}
}

//send the username to the server
//returns the id of the user if found, -1 otherwise
int searchFriend(const char *f){
	int id;
	char errorMessage[256];

	memset(errorMessage, 0, sizeof(errorMessage));

/*
	#ifdef DEBUG
		n = strlen("Friend's contact was not found!");
		errorMessage[n+1] = "Friend's contact was not found!";
	#endif
*/

	char userBuff[256];
	memset(userBuff, 0, sizeof(userBuff));
	strncpy(userBuff, "SEARCHFRIEND ", strlen("SEARCHFRIEND "));
	strncat(userBuff, f, strlen(f));

#ifdef DEBUG
	if (strncmp("SEARCHFRIEND Sky", userBuff, (strlen(userBuff)>strlen("SEARCHFRIEND Sky") ? strlen(userBuff):strlen("SEARCHFRIEND Sky")) ) == 0){
	sprintf(errorMessage, "FRIEND FOUND 6");
	}else{
        sprintf(errorMessage, "FRIEND NOT FOUND");
	}
#endif

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
                exit(0);
                //error("Error writing to the server.\n");
	}

        #ifdef DEBUG
        printf("message sent\n");
        #endif
        s = read(socketFD, errorMessage, sizeof(errorMessage) - 1);
        if(s < 0){
                exit(0);
        	//errorMessage
        }
	errorMessage[s] = 0;
#endif

	printf("Response: %s\n", errorMessage);
	
        if(strncmp("FRIEND FOUND", errorMessage, strlen("FRIEND FOUND")) == 0){
                sscanf(errorMessage, "%*s %*s %d", &id);
        }
        else{
                gtk_label_set_text(GTK_LABEL(AddFriendMessageLabel), errorMessage);
                gtk_widget_hide(AddButton);
		id = -1;
        }
        return(id);

}

////If the users clicks add
//it will send the friendID to the server to send friend request, if the user choose to add him
//prints "friend added"
void addFriend(GtkWidget *widget, login *data){

        char errorMessage[256];
        memset(errorMessage, 0, sizeof(errorMessage));

	char userBuff[256];
        memset(userBuff, 0, sizeof(userBuff));
	sprintf(userBuff, "REQUESTFRIEND %d %d", userIDGlobal, friend_id);

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
                exit(0);
                //error("Error writing to the server.\n");
        }

        #ifdef DEBUG
        printf("message sent\n");
        #endif
        s = read(socketFD, errorMessage, sizeof(errorMessage) - 1);
        if(s < 0){
                exit(0);
                //errorMessage
        }
        errorMessage[s] = 0;
#endif

#ifdef DEBUG
        sprintf(errorMessage, "FRIEND REQUEST SENT: TEST");
#endif

	printf("Response: %s\n", errorMessage);

               gtk_label_set_text(GTK_LABEL(AddFriendMessageLabel), errorMessage);
		gtk_widget_hide(AddButton);

return;
}

