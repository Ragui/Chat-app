#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serverDataStruct.h"
#include "serverAddFriend.h"



bool searchFriend(const char *Friend_username, char *errorMessage){

	for (int i = 0; i < contactsCount; i++){
                #ifdef DEBUG
//                printf("Contacts count: %d \n Friend's Username: %s", contactsCount, Friend_username);
                #endif
                int Ulen = (strlen(Friend_username) > strlen(accountsList[i].username) ? strlen(Friend_username) : strlen(accountsList[i].username));
                if(strncmp(Friend_username, accountsList[i].username, Ulen) == 0){
			sprintf(errorMessage, "FRIEND FOUND %d", i);
			return true;
		}}
	strcpy(errorMessage, "Friend not found");
        return false;
}

bool sendingFriendRequest(int userID, int friendID, char *errorMessage){
	int friendCount;
	friendCount = accountsList[userID].friendsCount;
	if(userID == friendID){
		sprintf(errorMessage, "FRIEND REQUEST NOT SENT!\n YOU CAN NOT ADD YOURSELF!");
		return false;
	}
	for (int i=0; i < friendCount; i++){
		if(friendID == accountsList[userID].friends[i]){
			sprintf(errorMessage, "FRIEND REQUEST NOT SENT!\n ALREADY FRIENDS!");
			return false;
		}
	}
	printf("UserID: %d, friendID: %d\n",userID, friendID);
	addRequest(userID, friendID);
	strncpy(errorMessage, "FRIEND REQUEST SENT",strlen("FRIEND REQUEST SENT"));	
	return true;
}

#ifdef DEBUG
int main(){
        char errorMessage[256];
        memset(errorMessage, 0, sizeof(errorMessage));
	
        contactsCount = 0;
        newAccount("Ragui", "Ragui", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
        newAccount("Jacob", "Jacob", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
        newAccount("Hoon", "Hoon", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
        newAccount("Daniel", "Daniel", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
        newAccount("Christian", "Christian", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
        newAccount("Jason", "Jason", "ra@yahoo.com", "12345pass", 3, "Cat:answer");

	for (int i=0; i<contactsCount; i++){
	        printf("Username : %s\n",accountsList[i].username);
	}
	const char *Nick = "Nick", *Ragui = "Ragui", *Jacob = "Jacob", *Hoon = "Hoon", *Daniel = "Daniel", *Christian = "Christian", *Jason = "Jason";

	searchFriend(Nick, errorMessage);
	printf("Search for: %s \nMessage Return: %s\n",Nick , errorMessage);
	searchFriend(Ragui, errorMessage);
        printf("Search for: %s \nMessage Return: %s\n",Ragui , errorMessage);
        searchFriend(Jacob, errorMessage);
        printf("Search for: %s \nMessage Return: %s\n",Jacob , errorMessage);
        searchFriend(Hoon, errorMessage);
        printf("Search for: %s \nMessage Return: %s\n",Hoon , errorMessage);
        searchFriend(Daniel, errorMessage);
        printf("Search for: %s \nMessage Return: %s\n",Daniel , errorMessage);
        searchFriend(Christian, errorMessage);
        printf("Search for: %s \nMessage Return: %s\n",Christian , errorMessage);
        searchFriend(Jason, errorMessage);
        printf("Search for: %s \nMessage Return: %s\n",Jason , errorMessage);


	printf("\n\nNOW TESTING SENDINGFRIENDREQUEST\n");
	sendingFriendRequest(0,1, errorMessage);
	printf("Ragui: userID 0 sending friend request to Jacob: userID 1 \nRespond from server: %s.\n", errorMessage);
        addFriend(1,0);
        sendingFriendRequest(0,1, errorMessage);
        printf("\nLet Imagine if Jacob accepted the request!\nSecond Run of Same Request!\nRagui: userID 0 sending friend request to Jacob: userID 1 \nRespond from server: %s.\n", errorMessage);

        return 0;
}

#endif
