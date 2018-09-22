#include "serverLogin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validLogin(const char *username,const char *password, char *errorMessage){
	for(int i = 0; i < contactsCount; i++){
		#ifdef DEBUG
		printf("Contacts count: %d \n", contactsCount);
		#endif
		int Ulen = (strlen(username) > strlen(accountsList[i].username) 
				? strlen(username) : strlen(accountsList[i].username));
		if(strncmp(username, accountsList[i].username, Ulen) == 0){
			int Plen = (strlen(password) > strlen(accountsList[i].password)
                                ? strlen(password) : strlen(accountsList[i].password));
			if(strncmp(password, accountsList[i].password, Plen) == 0){
				sprintf(errorMessage, "LOGIN OK %d", i);
				return i;
			}
			else{
				strcpy(errorMessage, "LOGIN does not match");
				return -1;
			}
		}
	}
	strcpy(errorMessage, "LOGIN not found"); 
	return -1;
}

#ifdef DEBUG

int main(){
	contactsCount = 0;
	newAccount("Ragui Halim", "ragui", "ra@yahoo.com", "12345pass", 3, "Cat:answer");
	char mes[26];
	printf("New account created.\n");
	validLogin("ragui", "123pass", mes);
	printf("Error message: %s\n", mes);
	validLogin("ragui", "12345pass", mes);
	printf("Error message: %s\n", mes);
	validLogin("ragui ", "12345pass", mes);
        printf("Error message: %s\n", mes);
}
#endif

//EOF
