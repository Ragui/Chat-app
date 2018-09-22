#ifndef clientFriendRequests_H
#define clientFriendRequests_H

#include "serverDataStruct.h"


void getRequests(int userID, int clientSocketFD);

void ApproveRequest(int userID, int friendID, bool accept);

#endif
