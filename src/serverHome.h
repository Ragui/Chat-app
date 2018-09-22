#ifndef serverHome_H
#define serverHome_H
#include "serverDataStruct.h"

void returnRequests(char *serverMessage, int userID);

void returnNumberFriends(char *serverMessage, int userID);

void returnContacts(char *serverMessage , int userID, int pos);

void deleteContact(char *serverMessage, int userID, int frID);
#endif

