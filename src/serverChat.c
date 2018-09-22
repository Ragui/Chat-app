#include "serverChat.h"
#include "serverDataStruct.h"
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


/* return the chat from the list*/
void returnChat( int user1, int user2, int lastUpdate, int clientSocketFD){
	int j, l, n;
	char *serverBuff, clientBuff[50];
	for(int i = 0; i < chatsCount; i++){
                if((user1 ==  chatList[i].users[0] && user2 ==  chatList[i].users[1]) ||
                        (user1 ==  chatList[i].users[1] && user2 ==  chatList[i].users[0])){
                        if(chatList[i].chatStart == chatList[i].chatEnd){
                                j = chatList[i].chatStart;
                                printf("%d: %s\n", chatList[i].history[j].senderID, chatList[i].history[j].text);
                                for(j = chatList[i].chatStart+1; j != chatList[i].chatEnd; j = (j+1) % 1000){
                                        printf("%d: %s\n", chatList[i].history[j].senderID, chatList[i].history[j].text);
                                }
                        }
                        else{
				serverBuff = malloc(sizeof(char) * 10);
				memset(serverBuff, 0, sizeof(serverBuff));
				sprintf(serverBuff, "chat %d", chatList[i].chatEnd - lastUpdate);	
				l = write(clientSocketFD, serverBuff, strlen(serverBuff));
                 	       	if(l < 0){
                        	        exit(0);
                        	}
				free(serverBuff);
                                for(j = lastUpdate; j < chatList[i].chatEnd; j++){
					
					n = read(clientSocketFD, clientBuff, sizeof(clientBuff));
       			                if(n < 0){
                                		exit(0);
                        		}
					int len = strlen(chatList[i].history[j].text) + 6;
					serverBuff = malloc(sizeof(char) * len);		
                                        memset(serverBuff, 0, sizeof(serverBuff));
					printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ %d %s\n", chatList[i].history[j].senderID, chatList[i].history[j].text);	
					sprintf(serverBuff, "%d %s", chatList[i].history[j].senderID, chatList[i].history[j].text);
					l = write(clientSocketFD, serverBuff, strlen(serverBuff));
                                	if(l < 0){
                                        	exit(0);
                                	}
                                	free(serverBuff);
                                }
                        }
                        break;
                }
        }	
}

/* save the message and its sender in the chat list*/
void saveMessage(char *m, int user1,int user2, int senderID){
	int i;
	message nm;
	nm.text = malloc(sizeof(char) * strlen(m));
	memset(nm.text, 0, sizeof(nm.text));
	strncpy(nm.text, m, strlen(m));
	nm.text[ strlen(m)] = 0;
	nm.senderID = senderID;
	for(i = 0; i < chatsCount; i++){
		if((user1 ==  chatList[i].users[0] && user2 ==  chatList[i].users[1]) || 
			(user1 ==  chatList[i].users[1] && user2 ==  chatList[i].users[0])){
			int *s = &chatList[i].chatStart;
			int *e = &chatList[i].chatEnd;
			chatList[i].history[*e] = nm;
			if(*e == *s){
				*s = (*s+1) % 1000;
			}
			*e = (*e+1) % 1000;
			break;
		}
	}
	if(i == chatsCount){
		int n = newChat(user1, user2);
		chatList[n].history[0] = nm;
		chatList[n].chatEnd++;
	}
}


#ifdef DEBUG
void printChat(int user1, int user2){
	int j;
	for(int i = 0; i < chatsCount; i++){
                if((user1 ==  chatList[i].users[0] && user2 ==  chatList[i].users[1]) ||
                        (user1 ==  chatList[i].users[1] && user2 ==  chatList[i].users[0])){
			if(chatList[i].chatStart == chatList[i].chatEnd){
				j = chatList[i].chatStart;
				printf("%d: %s\n", chatList[i].history[j].senderID, chatList[i].history[j].text);
				for(j = chatList[i].chatStart+1; j != chatList[i].chatEnd; j = (j+1) % 1000){
                			printf("%d: %s\n", chatList[i].history[j].senderID, chatList[i].history[j].text);
				}
			}
			else{
				for(j = chatList[i].chatStart; j < chatList[i].chatEnd; j++){
                                        printf("%d: %s", chatList[i].history[j].senderID, chatList[i].history[j].text);
                                }
			}
			break;
		}
        }

}

int main(){
	char s[30];
	chatsCount = contactsCount = 0;	
	int id = -2;
	int id1, id2;
	printf("Enter 2 ids: ");
	fgets(s, sizeof(s), stdin);
	sscanf(s,"%d %d", &id1, &id2);
	while(true){
		printf("Enter id and message: ");
		fgets(s, sizeof(s), stdin);		
		sscanf(s,"%d", &id);
		if(id == -1){
			break;}
		saveMessage(strchr(s,' ')+1, id1, id2, id);
	}
	printChat(id1,id2);
	printf("Chat count: %d\n",chatsCount);
	return 0;
}
#endif
