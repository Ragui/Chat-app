#ifndef serverAddFriend_H
#define serverAddFriend_H

#include "serverDataStruct.h"
#include <stdio.h>
#include <stdlib.h>

bool searchFriend(const char *Friend_username, char *errorMessage);

bool sendingFriendRequest(int userID, int friendID, char *errorMessage);


#endif
//EOF
