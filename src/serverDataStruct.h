#ifndef S_DS
#define S_DS

#define FNAME_LENGTH 26
#define LNAME_LENGTH 26
#define UNAME_LENGTH 26
#define EMAIL_LENGTH 26
#define PASSWORD_LENGTH 26
#define ENTRY_LENGTH 26

typedef struct clientAccount{
        char *fullName;
        char *username;
        int   ID;
        char *email;
        char *password;
        int question; /* 1 out of 5 possible security questions */
        char *answer;
        int   font;
        int   color;
	int status;
        int friends[100];//array of Id of friends
        int friendsCount;
        int requests[10];//array of Id of the friend who sent the request
        int requestsCount;
}account;

typedef struct mes{
        int senderID;
        char *text;
       // int messageID;
}message;

typedef struct Chat{
        int users[2];
        message history[1000];       //dynamic array for chat history
        int chatStart, chatEnd;
}chat;

typedef enum b{
        true = 1,
        false = 0
}bool;

void addMessageToChat(message m, chat c);
void addFriend(int friendID, int userID); // add friend in the friends list of user
void addRequest(int userID, int friendID);
int getStatus(int userID);
void setStatus(int userID, int stat);

int contactsCount;
account accountsList[500];

int chatsCount;
chat chatList[25000];

/* returns the id of the new account */
int newAccount(char *fullName, char *username, char *email, char *password, int question, char *ans);

bool searchByFullName(const char *fullName);

int newChat(int user1, int user2);
void error(const char *msg);
#endif
