#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include "clientDataStruct.h"
#include "clientLogin.h"
#include "clientFriendRequest.h"  
#include "clientHome.h"
#include "clientRegister.h"
/*#include "clientAddFriend.h"  
#include "clientResetPassword.h"  
*/
#include "clientChat.h"

#include <time.h>

int socketFD;
struct sockaddr_in serverAddress;

#ifndef testComm
/*void destroy( GtkWidget *widget,gpointer   data ){ 
    gtk_main_quit ();
    Exit = 1;
}*/
#endif

void mainLoop(){

	#ifndef testComm
	gtk_init(NULL, NULL);
	userIDGlobal = 0;
	printLogin(NULL,NULL);
	char userBuff[256], serverBuff[256];
	memset(userBuff,0, sizeof(userBuff));
	int u, s;
	while(Exit == 0){
		if (gtk_events_pending()){
			gtk_main_iteration();
		}
	}
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

	#endif 
	#ifdef testComm
	char userBuff[256], serverBuff[256];
	int u, s, l;
	int z = 0;
	while(z  < 10){
		//Open socket
		printf("Request: ");
		socketFD = socket(AF_INET, SOCK_STREAM, 0);
		if (socketFD < 0){
        		error("ERROR opening socket");
		}
		//conect to server
		if (connect(socketFD, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0){
			error("connecting to server failed");
	    	}
		int z1 = 0;
		while(z1 < 1){
			fgets(userBuff, sizeof(userBuff), stdin);
			l = strlen(userBuff);
			if (userBuff[l-1] == '\n'){
				userBuff[--l] = 0;
			}
			u = write(socketFD, userBuff, strlen(userBuff));
			if(u < 0){
				error("Error writing to the server.\n");
			}
			s = read(socketFD, serverBuff, 255);
			if(s < 0){
				error("Error reading from server.");
			}
			if(strncmp(serverBuff, "send message", strlen("send message")) == 0 ){
				z1 = -1;	
			}
			else if(strncmp(serverBuff, "chat", strlen("chat")) == 0 || 
					strncmp(serverBuff, "getrequests", strlen("getrequests")) == 0){
				sscanf(serverBuff, "%*s %d", &z1);
				z1 *= -1;
			}
			serverBuff[s] = 0;
			printf("Response: %s\n", serverBuff);
			printf("Request: ");
			z1++;
		}	
		close(socketFD);
	}
	#endif
}

int main(int argc, char *argv[]){
	Exit = 0;
	int portNum;
   	struct hostent *server;

	if (argc < 3) {
     	 	printf("Server host and/or port number are not provided.\n");
       		exit(0);
	}

	//intialize port
	portNum = atoi(argv[2]);
	if (portNum <= 2000){   
		printf("%s: invalid port number %d, should be greater 2000\n",argv[0], portNum);
       	 	exit(0);
    	}

	//get the server host
	server = gethostbyname(argv[1]);
	if (server == NULL) {
     	   printf("ERROR, no such host\n");
     	   exit(0);
    	}

	//initialize server address 
	memset(&serverAddress, 0, sizeof(serverAddress));
    	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNum);
	memcpy(&serverAddress.sin_addr.s_addr,
                server->h_addr_list[0], server->h_length);

	
	//main loop
	mainLoop();

	//exit
	printf("Exiting ....\n");

	return 0;
}




//EOF
