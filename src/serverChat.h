#ifndef serverChat_H
#define serverChat_H

#include "serverDataStruct.h"

/* return the chat from the list*/
void returnChat( int user1, int user2, int lastUpdate, int clientSocketFD);

/* save the message and its sender in the chat list*/
void saveMessage(char *m,int user1, int user2, int senderID);
#endif

