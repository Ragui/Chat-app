#include "clientChat.h"
#include "clientHome.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>

/* comment to commit*/
GtkWidget *sendChatButton, *chatEntry, *chatHomePageButton;
GtkWidget *chatBox1, *chatBox2, *chatBox3, *scrolledWindow, *chatBigBox;
GtkWidget *Window;
GtkWidget *mesTable, *friendName;
GdkPixbuf *homeBuff, *titleBuff;
GtkWidget *homeIcon, *titleIcon;
GtkWidget *messages[1000];
GtkWidget *messageBox[1000];
GtkTextBuffer *buf[1000];
GdkColor color;
int rows;
int dataSave[3];
int end = 0;

#ifdef DEBUG
	char *text;
#endif

void destroyWindow( GtkWidget *widget,gpointer   data ){
    Exit = 1;
	end = 1;
#ifdef DEBUG
gtk_main_quit();
printf("Exit chat page.\n");
#endif
}

void goHome(GtkWidget *widget,gpointer   data ){ 
	gtk_widget_destroy(Window);
#ifndef DEBUG
	printHome(NULL, userIDGlobal);
#endif
	end = 1;
#ifdef DEBUG
	printf("Go to home page\n");
	gtk_main_quit();
#endif
}

gboolean  callChat(void   *data ){
	if(end == 1){
		return FALSE;
	}
#ifdef DEBUG
	if(text != NULL){
#endif
	getChat(dataSave[0], dataSave[1]);	
#ifdef DEBUG
	}
#endif
	printf("Update the chat from server.\n");
	return TRUE;
}

//gets the messages in a chat from the server
void getChat(int user1, int user2){
#ifndef DEBUG
	extern int socketFD;
        extern struct sockaddr_in serverAddress;
	char userBuff[256], serverBuff[1000];
	int u = 0, s = 0;
	memset(userBuff, 0, sizeof(userBuff));
	memset(serverBuff, 0, sizeof(serverBuff));

        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD < 0){
                error("ERROR opening socket");
        }
	
        if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }

	sprintf(userBuff, "CHAT getchat %d %d %d", user1, user2, rows);
	u = write(socketFD, userBuff, strlen(userBuff));
	if(u < 0){
		error("Error writing to the server.\n");
	}

	s = read(socketFD, serverBuff, 255);
	if(s < 0){
		error("Error reading from server.");
	}
	printf("Response from getChat: '%s'\n", serverBuff);
        int i = 0, updates = 0;
	sscanf(serverBuff,"%*s %d", &updates);	
	printf("rows: %d updates: %d\n", rows, updates);
	gtk_table_resize (GTK_TABLE(mesTable),rows+updates > 0 ? rows+updates : 1,2);
        while(i < updates){
		u = write(socketFD, "next", strlen("next"));
		if(u < 0){
			error("Error writing to the server.\n");
		}

		memset(serverBuff, 0, sizeof(serverBuff));
		s = read(socketFD, serverBuff, 255);
		if(s < 0){
			error("Error reading from server.");
		}
		printf("Response: %s\n", serverBuff);
		char text[strlen(serverBuff)];
		memset(text, 0, sizeof(text));
		strncpy(text, strchr(serverBuff, ' ')+1, strlen(strchr(serverBuff, ' ')+1));
		int sender = -1;
		sscanf(serverBuff, "%d", &sender);
#endif
#ifdef DEBUG
		int sender = user1;
		int i = 0;
		int updates = 1;
		 gtk_table_resize (GTK_TABLE(mesTable),rows+1,2);
#endif
//		messageBox[i+rows]  = gtk_event_box_new ();
	//	messages[i+rows] = gtk_label_new(text);

		int ci = 0;
		int count = 0;
		if(text != NULL){
			count =	strlen(text);
		}
		char labelText[count+10];
		memset(labelText, 0, count+10);
    		while(count>20){
			strncat(labelText, &text[20*ci], 20);
			labelText[20*(ci+1)] = '\n';
			count -= 20;
			ci++;
		}
		if(count > 0){
			strncat(labelText, &text[20*ci], count);
		}
		
		messages[i+rows]  = gtk_label_new(labelText);
		messageBox[i+rows]  = gtk_event_box_new ();
                gtk_container_add (GTK_CONTAINER(messageBox[i+rows]), messages[i+rows]);
                gtk_table_attach(GTK_TABLE(mesTable), messageBox[i+rows], (sender == user1) ? 1 : 0, (sender == user1) ? 2 : 1
                        , i+rows+1,i+rows+2,(GtkAttachOptions)GTK_EXPAND,(GtkAttachOptions)GTK_FILL, (sender == user1) ?100:0, 1);

//		gtk_widget_modify_base(messages[i+rows], GTK_STATE_NORMAL,&color);
      //        gtk_container_add (GTK_CONTAINER(messageBox[i+rows]), messages[i+rows]);
        //	gtk_table_attach(GTK_TABLE(mesTable), messageBox[i+rows], 0, 1
	//		, i+rows+1,i+rows+2, (GtkAttachOptions)GTK_FILL,(GtkAttachOptions)GTK_FILL, (sender == user1) ?40:0, 1);        
	/*	gtk_table_attach_defaults(GTK_TABLE (mesTable), messageBox[i+rows],(sender == user1) ? 1 : 0, (sender == user1) ? 2 : 1
			 ,i+rows+1 ,i+rows+2);
	*/	
#ifndef DEBUG
		i++;
      }
#endif
	rows += updates;
	if(updates != 0){
		GtkAdjustment* adjustment;
		adjustment  = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (scrolledWindow));
		gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
		gtk_scrolled_window_set_vadjustment (GTK_SCROLLED_WINDOW (scrolledWindow), adjustment);
	}
	gtk_widget_show_all(Window);
#ifdef DEBUG
	text = NULL;
#endif	
}
//1- gets the chatID
//2- calls getChat
//3- prints the chat page with history messages
//	destroy old window
//	set the send button and input 
void printChat(GtkWidget *widget, int data[]){
	rows = 0;
	end = 0;
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(Window, 400, 500);
        gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
	GdkColor color;
	color.red = 0xFFFF;
	color.green = 0x5353;
	color.blue = 0x5353;
	gtk_widget_modify_bg(Window, GTK_STATE_NORMAL, &color);
	chatBigBox = gtk_vbox_new(FALSE, 1);

	/* Box 1 */
	chatBox1       = gtk_hbox_new(FALSE, 2);
	sendChatButton = gtk_button_new_with_label("Send");
	gtk_widget_set_size_request(sendChatButton, 100, 80);
	chatEntry      = gtk_text_view_new();
	gtk_widget_set_size_request(chatEntry, 297, 80);

	gtk_box_pack_end(GTK_BOX (chatBox1), sendChatButton, FALSE, FALSE, 0 );
	gtk_box_pack_end(GTK_BOX (chatBox1), chatEntry, FALSE, FALSE, 0 );
	
	/* Box 2*/
	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

	/* tabel for messages */
	mesTable = gtk_table_new (1, 2,FALSE);
	gtk_table_set_row_spacings (GTK_TABLE(mesTable),1);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledWindow),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledWindow),GTK_SHADOW_NONE);
	
	chatBox2 = gtk_hbox_new(FALSE, 2);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW (scrolledWindow) , mesTable);	

	gtk_box_pack_end(GTK_BOX (chatBox2), scrolledWindow, TRUE, TRUE, 0 );

	/* chat box 3*/
	chatBox3       = gtk_hbox_new(FALSE, 0);
	titleBuff = gdk_pixbuf_new_from_file_at_size("Icons/title.png", 350, 60,NULL);
	homeBuff  = gdk_pixbuf_new_from_file_at_size("Icons/home.png", 30, 60, NULL);

	homeIcon = gtk_image_new_from_pixbuf (homeBuff);
	titleIcon = gtk_image_new_from_pixbuf (titleBuff);
	gtk_widget_set_size_request(titleIcon, 350, 70);
	gtk_widget_set_size_request(homeIcon, 30, 60);
	chatHomePageButton = gtk_button_new ();
//	gtk_widget_set_size_request(chatHomePageButton, 30, 60);
	gtk_button_set_image (GTK_BUTTON (chatHomePageButton), homeIcon);

	gtk_box_pack_end(GTK_BOX (chatBox3), titleIcon, FALSE, FALSE, 0 );
	gtk_box_pack_end(GTK_BOX (chatBox3), chatHomePageButton, FALSE, FALSE, 0 );
	
	/* big box*/
	friendName = gtk_label_new("friend name"); 
	gtk_widget_set_size_request(chatBox1, 400, 80);	
	gtk_widget_set_size_request(chatBox2, 400, 360);
	gtk_widget_set_size_request(chatBox3, 400, 50);
	gtk_box_pack_end(GTK_BOX (chatBigBox), chatBox1, TRUE, TRUE, 0 );
	gtk_box_pack_end(GTK_BOX (chatBigBox), chatBox2, TRUE, TRUE, 0 );
	gtk_box_pack_end(GTK_BOX (chatBigBox), friendName, TRUE, TRUE, 0 );
	gtk_box_pack_end(GTK_BOX (chatBigBox), chatBox3, TRUE, TRUE, 0 );

	/* window */
	gtk_container_add (GTK_CONTAINER (Window), chatBigBox);
	getChat(data[0], data[1]);		
	gtk_widget_show_all(Window);
	dataSave[0] = data[0];
	dataSave[1] = data[1];

	g_signal_connect(Window,"delete-event",G_CALLBACK(destroyWindow),NULL);	
	g_signal_connect(sendChatButton,"clicked",G_CALLBACK(sendMessage),dataSave);		
	g_signal_connect(chatHomePageButton,"clicked",G_CALLBACK(goHome),data);
	g_timeout_add_seconds(2,callChat ,NULL );
}

//1- gets the message when the button is clicked
//2- send the message to the server
//3- print the updated chat
void sendMessage(GtkWidget *widget, int data[]){
#ifdef DEBUG
	printf("Send message to server.\n");
	GtkTextIter start, end;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(chatEntry));
        gtk_text_buffer_get_bounds (buffer, &start, &end);
        text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
#endif
#ifndef DEBUG
	extern int socketFD;
	extern struct sockaddr_in serverAddress;
        char userBuff[256], serverBuff[1000];
        char *textMessage;
	int u = 0, s = 0;
        memset(userBuff, 0, sizeof(userBuff));
        memset(serverBuff, 0, sizeof(serverBuff));

        socketFD = socket(AF_INET, SOCK_STREAM, 0);
	printf("userID: %d ---- friendID: %d\n",data[0], data[1]);	
        if (socketFD < 0){
                error("ERROR opening socket");
        }

        if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
                error("connecting to server failed");
        }
	GtkTextIter start, end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(chatEntry));
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	textMessage = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

	int lenMess = strlen(textMessage) + 6;

        sprintf(userBuff, "CHAT savemessage %d %d %d", data[0], data[1], lenMess);
        u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }

        s = read(socketFD, serverBuff, 255);
        if(s < 0){
                error("Error reading from server.");
        }
        printf("Response from SaveMessage: '%s'\n", serverBuff);
	memset(userBuff, 0, sizeof(userBuff));
        memset(serverBuff, 0, sizeof(serverBuff));
	
	sprintf(userBuff,"%d %s", userIDGlobal, textMessage);
	u = write(socketFD, userBuff, strlen(userBuff));
        if(u < 0){
                error("Error writing to the server.\n");
        }

        s = read(socketFD, serverBuff, 255);
        if(s < 0){
                error("Error reading from server.");
        }
        printf("Response from SaveMessage 2: '%s'\n", serverBuff);
	getChat(data[0], data[1]);
	memset(textMessage, 0, sizeof(textMessage));	
#endif
}

//1- when the button is clicked, the corresponding message is deleted
//2- send the update to the server
//3- prints the updated chat
void deleteMessage(GtkWidget *widget, int messageID);

//1- when the button is clicked, the chat history is deleted
//2- send the update to the server
//3- prints the updated chat
void DeleteAll(GtkWidget *widget, int messageID);


#ifdef DEBUG
int main(){
	gtk_init(NULL, NULL);
	int x[] = {0,1};
	printChat(NULL, x);
	gtk_main();	
	return 0;
}
#endif

