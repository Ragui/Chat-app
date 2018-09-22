#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "serverDataStruct.h"

void error(const char *msg){
        perror(msg);
        exit(1);
}

int getStatus(int userID){
	return accountsList[userID].status;
}

void setStatus(int userID, int stat){
	if(userID < contactsCount){
	accountsList[userID].status = stat;
	printf("UserId = %d, status = %d\n", userID, stat);
	}
}

void addFriend(int friendID, int userID){
	accountsList[userID].friends[accountsList[userID].friendsCount] = friendID;
        accountsList[userID].friendsCount++;

	accountsList[friendID].friends[accountsList[friendID].friendsCount] = userID;
        accountsList[friendID].friendsCount++;
}

/* a friend sent a friend request to the user*/
void addRequest(int userID, int friendID){
	accountsList[friendID].requests[accountsList[friendID].requestsCount] = userID;
	accountsList[friendID].requestsCount++;
}

int newAccount(char *fullName, char *username, char *email, char *password, int question, char *ans){
	bool alreadyRegistered;
	 
	alreadyRegistered = searchByFullName(username);
	
	if(!alreadyRegistered)
	{
		account x = {fullName, username, contactsCount, email, password, question, ans, 0, 0, 0, {-1}, 0, {-1}, 0};
		accountsList[contactsCount++] = x;  
		return contactsCount-1;
	}
	else
	{
		return -1;
	}	
}

bool searchByFullName(const char *fullName)
{
	for(int i = 0; i < contactsCount; i++)
	{
		int Ulen = (strlen(fullName) > strlen(accountsList[i].username) ? strlen(fullName): strlen(accountsList[i].username));
		if(strncmp(fullName, accountsList[i].username, Ulen) == 0){
			return true;
		}	
	}
	return false;
}


int newChat(int user1, int user2){
	chat x;
	x.chatStart = x.chatEnd = 0;
	x.users[0] = user1;
	x.users[1] = user2;
	chatList[chatsCount++] = x; 
	return chatsCount-1;
}

#ifdef DEBUG
static void printAccount(int ID){
	printf("Full name: %s\n",accountsList[ID].fullName);
	printf("Username : %s\n",accountsList[ID].username);  
	printf("ID       : %d\n",accountsList[ID].ID);
	printf("Email    : %s\n",accountsList[ID].email);
	printf("answer   : %s\n",accountsList[ID].answer);
}

static void printRequests(int ID){
	for(int i = 0; i < accountsList[ID].requestsCount; i++){
		printf("%d: %d\n",i,accountsList[accountsList[ID].requests[i]].ID);
	} 
}

static void printFriends(int ID){
        for(int i = 0; i < accountsList[ID].friendsCount; i++){
                printf("%d: %d\n",i,accountsList[accountsList[ID].friends[i]].ID);
        }
}
#endif

/*
#ifdef DEBUG
int main(){
	contactsCount = 0;		
	int user1 = newAccount("Ragui Halim", "user1", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
	int user2 = newAccount("Ragui Halim", "user2", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
	int user3 = newAccount("Ragui Halim", "user3", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
	addRequest(user1, user2);
	addRequest(user1, user3);
//	printRequests(user1);

	addFriend(user1, user2);
	addFriend(user1, user3);
	printFriends(user1);
	return 0;
}
#endif*/
