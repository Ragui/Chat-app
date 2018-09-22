#include "serverHome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void returnRequests(char *serverMessage, int userID){
    sprintf(serverMessage, "Requests: %d", accountsList[userID].requestsCount);
}

void returnNumberFriends(char *serverMessage, int userID){
    sprintf(serverMessage, "Contacts: %d", accountsList[userID].friendsCount);
}


void returnContacts(char *serverMessage, int userID, int pos){
	int fID = accountsList[accountsList[userID].friends[pos]].ID;
    sprintf(serverMessage, "Contact: %d %s %d", fID, accountsList[fID].username, accountsList[fID].status);
}

void deleteContact(char *serverMessage, int userID, int frID){
        
	int n;
	n = accountsList[userID].friendsCount;
        if (n > 0){	//if server is slow it could delete multiple times
		 
		accountsList[accountsList[userID].friends[frID]].ID = accountsList[accountsList[userID].friends[n]].ID;
		accountsList[userID].friendsCount = n-1;
	
		sprintf(serverMessage, "Contact %d deleted", frID);
	}
	else{
		sprintf(serverMessage, "Contact list is empty");
	}
	
}

