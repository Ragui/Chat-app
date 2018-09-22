#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include "serverDataStruct.h"
#include "serverLogin.h"
#include "serverChat.h"
#include "serverFriendRequest.h"
#include "serverHome.h"
#include "serverAddFriend.h"
#include "serverResetPassword.h"
#include "serverRecoverPassword.h"
int Shutdown = 0, Exit = 0;


void HandleClient(int clientSocketFD){
	int l, n;
	char serverBuff[256];
	char clientBuff[256];
	memset(clientBuff, 0, sizeof(clientBuff));
	memset(serverBuff, 0, sizeof(serverBuff));	

	n = read(clientSocketFD, clientBuff, sizeof(clientBuff));

	if(n < 0){
		error("Error reading from client.");
	}

	clientBuff[n] = 0;
//	#ifdef DEBUG
    		printf("Received message: %s\n", clientBuff);
//	#endif

	//handle different messages
	if(strcmp(clientBuff, "Shutdown") == 0){
		Shutdown = 1;
		strncpy(serverBuff, "Shutdown", sizeof(serverBuff));			
	}
	else if(strcmp(clientBuff, "Exit") == 0){
		Exit = 1;
                strncpy(serverBuff, "Exit", sizeof(serverBuff));
        }
	/* The buffer should be in the form LOGIN username password*/
	else if(strncmp(clientBuff, "LOGIN", 5) == 0){
		char *temp = strchr(clientBuff, ' ')+1;
		char *password = strchr(temp, ' ')+1;
		char username[25];
		memset(username, 0, sizeof(username));		
		strncpy(username, temp, (strlen(temp)-strlen(password)-1));

		char errorMessage[100]; 
		memset(errorMessage, 0, sizeof(errorMessage));		
		printf("username: '%s'\npassword: '%s'\n",username, password);

		int val = validLogin(username, password, errorMessage);
		if(val != -1){
			setStatus(val, 1);
		}
		strncpy(serverBuff, errorMessage , strlen(errorMessage));
	}
	else if(strncmp(clientBuff, "GET REQUESTS",12) == 0){
		int IDr;
		sscanf(clientBuff,"%*s %*s %*s %*s %d", &IDr);
		returnRequests(serverBuff,IDr);
	}	
	else if(strncmp(clientBuff, "GET N CONTACTS", 14) == 0){
                int IDc;
                sscanf(clientBuff, "%*s %*s %*s %*s %*s %d", &IDc);
		returnNumberFriends(serverBuff, IDc);
        }
	else if(strncmp(clientBuff, "GET CONTACT", 11) == 0){
		int IDuser, contact;
		sscanf(clientBuff, "%*s %*s %d %*s %*s %d", &contact, &IDuser);
		returnContacts(serverBuff, IDuser, contact);
	}
	
	else if(strncmp(clientBuff, "DELETE CONTACT", 14) == 0){
                int IDuser, contact;
                sscanf(clientBuff, "%*s %*s %d %*s %*s %d", &contact, &IDuser);
                deleteContact(serverBuff, IDuser, contact);
        }

	else if(strncmp(clientBuff, "CHAT", 4) == 0){
		char order[20], temp[5];
		int  user1, user2;
		int  messageLen = 0;
		memset(temp, 0, sizeof(temp));
		memset(order, 0, sizeof(order));
		sscanf(clientBuff, "%s %s %d %d %d", temp, order, &user1, &user2, &messageLen);

		
		
		if(strncmp(order, "getchat", strlen("getchat")) == 0){	
		//	printChat(user1, user2);
			returnChat( user1,user2, messageLen, clientSocketFD);
		}
		else if (strncmp(order, "savemessage", strlen("savemessage")) == 0){
			l = write(clientSocketFD, "send message", strlen("send message"));
        		if(l < 0){
                		error("Error writing to the client.\n");
        		}
			char tempBuff[messageLen];
			memset(tempBuff, 0, messageLen);

        		n = read(clientSocketFD, tempBuff, messageLen);
        		if(n < 0){
                		error("Error reading from client.");
        		}
			printf("Recived message 2: %s\n",tempBuff);

			int senderID = -1;
			sscanf(tempBuff,"%d", &senderID); 
			char *text = strchr(tempBuff, ' ')+1;
			sprintf(serverBuff, "Sender ID: %d .. text: '%s'", senderID, text);
			saveMessage(text,user1,user2,senderID);	
		}
	}
	else if(strncmp(clientBuff, "FRIENDREQUEST", strlen("FRIENDREQUEST")) == 0){
		char order[20];
                int  IDuser = -1, friendID = -1;
                memset(order, 0, sizeof(order));
		sscanf(clientBuff, "%*s %s %d", order, &IDuser);

		if(strncmp(order, "getrequests", strlen("getrequests")) == 0){
			getRequests(IDuser, clientSocketFD);		
		}
		else if(strncmp(order, "accept", strlen("accept")) == 0){
			sscanf(clientBuff, "%*s %*s %*d %d", &friendID);	
			ApproveRequest(IDuser,friendID, true);	
		}
		else if(strncmp(order, "decline", strlen("decline")) == 0){
                        sscanf(clientBuff, "%*s %*s %*d %d", &friendID);
                        ApproveRequest(IDuser,friendID, false);
                }
		memset(serverBuff, 0, sizeof(serverBuff));	

	}
        else if(strncmp(clientBuff, "SEARCHFRIEND", strlen("SEARCHFRIEND")) == 0){
		char name[20];
                char errorMessage[256];
                memset(errorMessage, 0, sizeof(errorMessage));
		memset(name, 0, sizeof(name));
		sscanf(clientBuff, "%*s %s", name);
		searchFriend(name, errorMessage); 
		sprintf(serverBuff, errorMessage);
	}
	else if(strncmp(clientBuff, "REQUESTFRIEND", 13) == 0){
		int userID, friendID;
                char errorMessage[256];
                memset(errorMessage, 0, sizeof(errorMessage));
		sscanf(clientBuff, "%*s %d %d", &userID, &friendID);
		sendingFriendRequest(userID, friendID, errorMessage);
		sprintf(serverBuff, errorMessage);
	}
	else if(strncmp(clientBuff, "REGISTER", 8) == 0)
        {

                char fullName[40];
                char fName[FNAME_LENGTH];
                char lName[LNAME_LENGTH];
                char uName[UNAME_LENGTH];
                char email[EMAIL_LENGTH];
                char password[PASSWORD_LENGTH];
               // char *temp = strchr(clientBuff, ' ')+1;
      //          char *question = "Zot and Go or nah?";
      		int question;
                char answer[26];;
                char errorMessage[100];
                int userID;

                memset(errorMessage, 0, sizeof(errorMessage));

              /*  int i, j = 0, ctr = 0;
                int k = 0;

                for(i = 0; i <= strlen(temp); i++){
                    if(temp[i] == ' ' || temp[i] == '\0'){
                        if(ctr == 0){
                                fName[j] = '\0';
                                fullName[j] = ' ';
                                k = j;
                               k++;
                        }
                        if(ctr == 1){
                                lName[j] = '\0';
                                fullName[j + k] = '\0';
                        }
                        if(ctr == 2){
                                uName[j] = '\0';
                        }
                        if(ctr == 3){
                                email[j] = '\0';
                        }
                        if(ctr == 4){
                                password[j] = '\0';
                        }
                        ctr++;
                        j = 0;
                    }
                    else{
                        if(ctr == 0){
                                fName[j] = temp[i];
                                fullName[j] = temp[i];
                                k = j;
                        }
			if(ctr == 1){
                                lName[j] = temp[i];
                                fullName[k + j] = temp[i];
                        }
                        if(ctr == 2){
                                uName[j] = temp[i];
                        }
                        if(ctr == 3){
                                email[j] = temp[i];
                        }
                        if(ctr == 4){
                                password[j] =temp[i];
                        }
                        j++;
                    }
                }*/

		sscanf(clientBuff, "%*s %s %s %s %s %s %d %s", fName, lName, uName, email, password, &question, answer);
		strcpy(fullName, fName);
		strcat(fullName, " ");
		strcat(fullName, lName);

                #ifndef DEBUG
                printf("Full Name:  %s\n", fullName);
                printf("First Name: %s\n", fName);
                printf("Last Name:  %s\n", lName);
                printf("Username:   %s\n", uName);
                printf("email:      %s\n", email);
                printf("password:   %s\n", password);
		printf("question:   %d\n", question);
		printf("answer:     %s\n", answer);
               #endif

                userID = newAccount(fullName, uName, email, password, question, answer);
		//printAccount(userID);
                if(userID == -1)
                {
                        strcpy(errorMessage, "Unable to complete registration");
                }
                else
                {
                        sprintf(errorMessage, "REGISTER OK %d", userID);
			setStatus(userID, 1);
                }
		strncpy(serverBuff, errorMessage, strlen(errorMessage));
        }
	else if(strncmp(clientBuff, "RECOVER", 7) == 0){
		/*char *temp = strchr(clientBuff, ' ')+1;
                char *temp2 = strchr(temp, ' ')+1;
		char *Answer = strchr(temp2, ' ')+1;*/
                char username[25];
		int question;
		char answer[26];
                memset(username, 0, sizeof(username));
               /* strncpy(username, temp, (strlen(temp)-strlen(temp2)-1));
		strncpy(Squestion,temp2, (strlen(temp2)-strlen(Answer)-1));*/
		sscanf(clientBuff,"%*s %s %d %s", username, &question, answer);	

                char errorMessage[100];
                memset(errorMessage, 0, sizeof(errorMessage));
		#ifdef DEBUG
                printf("username: '%s'\nquestion: '%d'\n answer: '%s'\n",username, question, answer);
		#endif

                validRecover(username, question, answer, errorMessage);
                strcpy(serverBuff, errorMessage);

	}
	else if(strncmp(clientBuff, "RESET", 5) == 0){
		/*char *temp = strchr(clientBuff, ' ')+1;
		char *temp1 = strchr(temp, ' ')+1;
                char *temp2 = strchr(temp1, ' ')+1;
                char *temp3 = strchr(temp2, ' ')+1;
		char *Answer = strchr(temp3, ' ')+1;
		char username[25];
                char currentpw[25];
		char newpw[25];
                char Squestion[7];
                memset(username, 0, sizeof(username));
                strncpy(username, temp, (strlen(temp)-strlen(temp1)-1));
                strncpy(currentpw,temp1, (strlen(temp1)-strlen(temp2)-1));
		strncpy(newpw, temp2, (strlen(temp2) - strlen(temp3)-1));
		strncpy(Squestion, temp3, (strlen(temp3) - strlen(Answer)-1));*/
		int userID;
		char currentpw[25];
		char newpw[25];
		char Squestion[7];
		char Answer[25];

		//memset(userID, 0, sizeof(userID));

		sscanf(clientBuff,"%*s %d %s %s %s %s", &userID, currentpw, newpw, Squestion, Answer);
                char errorMessage[100];
                memset(errorMessage, 0, sizeof(errorMessage));
		#ifdef DEBUG
                printf("userID: '%d'\ncurrentpw: '%s'\nnewpw: '%s'\nSquestion: '%s'\nanswer: '%s'\n",userID,currentpw, newpw, Squestion, Answer);
		#endif

                validReset(userID,currentpw, newpw, Squestion, Answer, errorMessage);
                strcpy(serverBuff, errorMessage);

	}
	else if(strncmp(clientBuff, "LOGOFF", strlen("LOGOFF")) == 0){
		strcpy(serverBuff,"OK" );
		int uid = -1;
		sscanf(clientBuff, "%*s %d", &uid);
		setStatus(uid, 0);
	}
	else{
		 strncpy(serverBuff, "Command not found!"  , strlen("Command not found!"));
	}	
	l = write(clientSocketFD, serverBuff, strlen(serverBuff));
	if(l < 0){
		error("Error writing to the client.\n");
	}
}

void initial();

void mainLoop(int serverSocketFD, int timeout ){
	initial();
	int clientSocketFD;
        socklen_t clientLen;
	struct sockaddr_in  clientAddress;
    	fd_set ActiveFDs;   /* socket file descriptors to select from */
    	fd_set ReadFDs;     /* socket file descriptors ready to read from */
	FD_ZERO(&ActiveFDs);                /* set of active sockets */
	FD_SET(serverSocketFD, &ActiveFDs);   /* server socket is active */

    	struct timeval TimeVal;
    	int res;


	printf("Starting main loop.\n");

	
        int user1 = newAccount("Team 11", "chatbot", "ra@yahoo.com", "123456", 3, "Cat:answer");
	int user2 = newAccount("Rainer Doemer","doemer", "rd@yahoo.com", "123456", 3, "Cat:answer");
	int user3 = newAccount("QV", "QV", "qv@yahoo.com", "123456", 3, "Cat:answer");	
	addFriend(user1, user2);
	addFriend(user1,user3);
	addFriend(user2, user3);

	while (Shutdown == 0){
		ReadFDs = ActiveFDs;
        	TimeVal.tv_sec  = timeout / 1000000;    /* seconds */
        	TimeVal.tv_usec = timeout % 1000000;    /* microseconds */
       		/* block until input arrives on active sockets or until timeout */
        	res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);

		if(res < 0){	/*error*/
			error("Error: Select failed.\n");
		}
		else if(res == 0){	/*timeout*/
			#ifdef DEBUG
				printf("Timeout\n");
			#endif
		}	
		else{	/*There are clients to serve*/
			for(int i = 0; i < FD_SETSIZE ; i++){
				if( !FD_ISSET(i, &ReadFDs)) continue;
				if(i == serverSocketFD){
					printf("Dealing with new client'\n");
					clientLen = sizeof(clientAddress);
                        		clientSocketFD = accept(serverSocketFD,(struct sockaddr*)&clientAddress, &clientLen);
					if (clientSocketFD < 0)
                        		{   error("data socket creation (accept) failed");
                        		}
					printf("Client %d is conected.\n", i);		
					FD_SET(clientSocketFD, &ActiveFDs);
				}
				else{
					printf("Dealing with existing client, %d.\n",i);
					HandleClient(i);
                                        printf("Closing client %d coonection.\n", i);
					close(i);
					FD_CLR(i, &ActiveFDs);	
				}
			}	
		}
	}		
}

int main(int argc, char *argv[]){
        int serverSocketFD, portNum;
        struct sockaddr_in  serverAddress;

        if(argc < 2){
                printf("Insufficient arguments to start the server.\n");
                exit(1);
        }

        //creat socket
        serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
        if(serverSocketFD < 0){
                error("Error creating the socket for the server.\n");
        }

        portNum = atoi(argv[1]);
        if(portNum <= 2000){
                printf("Invalid port number.\n");
        }

	//server Address
	memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(portNum);
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	//binding
	if (bind(serverSocketFD, (struct sockaddr *) &serverAddress ,sizeof(serverAddress)) < 0){
              error("Erorr on binding");
        }

	//listening
	if (listen(serverSocketFD, 5) < 0){
                error("Error on listenning.\n");
        }
        printf("Server is listenning ... \n");

#ifdef DEBUG
	printf("Calling main finction.\n");
#endif
	//main loop
	mainLoop(serverSocketFD, 250000);

	//Shutdown
	printf("Server is shutting down.\n");
        close(serverSocketFD);
	return 0;
}

void initial(){
	contactsCount = 0; /* later we will load it from the data file*/
	chatsCount = 0;
}
