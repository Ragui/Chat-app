#include "serverRecoverPassword.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifndef DEBUG
bool validRecover(const char *username,int question, const char *Answer, char *errorMessage){
#endif

#ifdef DEBUG
int main(){
	int contactsCount;
	contactsCount = newAccount("Ragui Halim", "client1", "ra@yahoo.com", "123456", 3, "Cat:answer");
	contactsCount = newAccount("Ragui Halim", "client2", "ra@yahoo.com", "ABCDEF", 3, "Cat:answer");
	contactsCount = newAccount("Ragui Halim", "client3", "ra@yahoo.com", "654321", 3, "Cat:answer");
	const char *username = "client2";
	const char *Squestion = "Three";
	const char *Answer = "Cat:answer";
	char *errorMessage = malloc(256);
#endif
       /* int question;
        if(strcmp(Squestion, "One") == 0){
                question = 1;
        }
        else if(strcmp(Squestion, "Two") == 0){
                question = 2;
        }
        else if(strcmp(Squestion, "Three") == 0){
                question = 3;
        }
        else if(strcmp(Squestion, "Four") == 0){
                question = 4;
        }
        else if(strcmp(Squestion, "Five") == 0){
                question = 5;
        }
        else{
                question = -1;
        }*/

        printf("Question number is %d\n", question);

        for(int i = 0; i < contactsCount; i++){
                if (strcmp(username, accountsList[i].username) == 0 && (strlen(username) == strlen(accountsList[i].username))){
                        if((question == accountsList[i].question) && strcmp(Answer, accountsList[i].answer) == 0 && (strlen(Answer) == strlen(accountsList[i].answer))){
                                sprintf(errorMessage, "RECOVER OK %s", accountsList[i].password);
                                #ifdef DEBUG
                                printf("Matching username is %s. Password is %s\n", accountsList[i].username, accountsList[i].password);
                                printf("%s\n", errorMessage);
                                #endif
                                return true;
                        }
                        else{
                                strcpy(errorMessage, "RECOVER does not match");
				#ifdef DEBUG
                                printf("%s\n", errorMessage);
				#endif
                                return false;
                        }


                }
        }
        strcpy(errorMessage, "RECOVER not found");
	#ifdef DEBUG
        printf("%s\n", errorMessage);
        #endif
        return false;
}

