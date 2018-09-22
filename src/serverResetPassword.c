#include "serverResetPassword.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void validReset(int userID, const char *currentpw,char *newpw, const char *Squestion, const char *Answer, char *errorMessage){
	int question;
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
        }

       // printf("Question number is %d\n", question);
	printf("Current Password for %s is %s\n", accountsList[userID].username, accountsList[userID].password);
	if(strcmp(currentpw, accountsList[userID].password) == 0 && (strlen(currentpw) == strlen(accountsList[userID].password))){
		 if((question == accountsList[userID].question) && (strcmp(Answer, accountsList[userID].answer) == 0) 
			&& (strlen(Answer) == strlen(accountsList[userID].answer))){
                                accountsList[userID].password = newpw;
                                strcpy(errorMessage, "RESET OK");
                              //  #ifdef DEBUG
                                printf("Matching username is %s. Old Password is %s. New Password is %s.\n", accountsList[userID].username, currentpw
				, accountsList[userID].password);
                                printf("%s\n", errorMessage);
                              //  #endif
                                return;
		}
	}
	else{
		 strcpy(errorMessage, "RESET does not match");
	         printf("%s\n", errorMessage);
       		 return;
		
	}

           

	/*for(int i = 0; i < contactsCount; i++){
		if ((strcmp(username, accountsList[i].username) ==  0) && (strlen(username) == strlen(accountsList[i].username))){
			printf("Current Password for %s is %s\n", accountsList[i].username, accountsList[i].password); 
               		if ((strcmp(currentpw, accountsList[i].password) == 0) && (strlen(currentpw) == strlen(accountsList[i].password))){
                       		 if((question == accountsList[i].question) && (strcmp(Answer, accountsList[i].answer) == 0) && (strlen(Answer) == strlen(accountsList[i].answer))){
					accountsList[i].password = newpw;
                               		strcpy(errorMessage, "RESET OK");
                               		//#ifdef DEBUG
                              		printf("Matching username is %s. Old Password is %s. New Password is %s.\n", accountsList[i].username, currentpw, accountsList[i].password);
                               		printf("%s\n", errorMessage);
                               		//#endif
                               		return;
                       		 }
				else{
					break;
				}
               		}
			else{
					break;
			}
		}
        }*/
}
