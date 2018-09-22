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
#include "serverFriendRequest.h"
#include "serverDataStruct.h"

void getRequests(int userID, int clientSocketFD){
	char userBuff[20];
	char serverBuff[30];
	int l = -1, n = -1;
	memset(userBuff, 0, sizeof(userBuff));
	sprintf(userBuff, "requests %d", accountsList[userID].requestsCount);

	l = write(clientSocketFD, userBuff, strlen(userBuff));
	if(l < 0){
		error("Error writing to the client.\n");
	}

	int friendID = -1;
	for(int i = 0; i < accountsList[userID].requestsCount; i++){
		memset(serverBuff, 0, sizeof(serverBuff));	
		friendID = accountsList[userID].requests[i];
		sprintf(serverBuff, "%d %s", friendID, accountsList[friendID].username);
		
		n = read(clientSocketFD, userBuff, sizeof(userBuff));
		if(n < 0){
			error("Error reading from client.");
		}

		l = write(clientSocketFD, serverBuff, strlen(serverBuff));
		if(l < 0){
			error("Error writing to the client.\n");
		}

	}
}

void ApproveRequest(int userID, int friendID, bool accept){
	if(accept == true){
		addFriend(userID, friendID);
	}
	printf("%d %d\n",userID, friendID);
	for(int i = 0; i <  accountsList[userID].requestsCount; i++){
		if(friendID == accountsList[userID].requests[i]){
			accountsList[userID].requests[i] = accountsList[userID].requests[accountsList[userID].requestsCount - 1];
			accountsList[userID].requestsCount--;
			break;
		}	
	}	
}

