#makefile

CFLAGS = gcc -ansi -std=c99 -Wall $(DEBUG)
GUI = `pkg-config --cflags --libs gtk+-2.0`

all: chat server

test:chat server
	../bin/server 5200 &
	../bin/chat zuma 5200

clean:	
	rm -f *.o
	rm -f ../bin/chat ../bin/server test-comm
	rm -f *.out

#main
#client: clientMain.o clientAddFriend.o clientHome.o clientFriendRequest.o clientLogin.o clientRegister.o clientSettings.o clientChat.o clientResetPassword.o
#	$(CFLAGS) clientMain.o clientAddFriend.o clientHome.o clientFriendRequest.o clientLogin.o clientRegister.o clientSettings.o clientChat.o clientResetPassword.o -o client

#chat:  clientMain.o clientLogin.o clientDataStruct.o clientHome.o
#	$(CFLAGS) clientMain.o clientLogin.o clientDataStruct.o clientHome.o -o ../bin/chat $(GUI)

#server: serverMain.o serverDataStruct.o serverLogin.o 
#	$(CFLAGS) serverMain.o serverLogin.o serverDataStruct.o -o ../bin/server

chat:  clientMain.o clientLogin.o clientDataStruct.o clientChat.o clientFriendRequest.o clientHome.o clientRegister.o clientAddFriend.o clientResetPassword.o clientRecoverPassword.o clientSettings.o
	$(CFLAGS) clientMain.o clientLogin.o clientDataStruct.o clientChat.o clientFriendRequest.o clientHome.o clientRegister.o clientAddFriend.o clientResetPassword.o clientRecoverPassword.o clientSettings.o -o ../bin/chat $(GUI)

server: serverMain.o serverDataStruct.o serverLogin.o serverAddFriend.o serverChat.o serverFriendRequest.o serverHome.o serverResetPassword.o serverRecoverPassword.o
	$(CFLAGS) serverMain.o serverLogin.o serverAddFriend.o serverDataStruct.o serverFriendRequest.o serverChat.o serverHome.o serverResetPassword.o serverRecoverPassword.o -o ../bin/server

settings: clientSettings.o
	$(CFLAGS) clientSettings.o -o settings $(GUI)

# .o client files
clientMain.o: clientMain.c clientAddFriend.h clientHome.h clientFriendRequest.h clientLogin.h clientRegister.h clientSettings.h clientChat.h clientResetPassword.h clientDataStruct.h
	$(CFLAGS) -c clientMain.c -o clientMain.o $(GUI)

clientHome.o: clientHome.h clientHome.c clientDataStruct.h
	$(CFLAGS) -c clientHome.c -o clientHome.o $(GUI)

clientFriendRequest.o: clientFriendRequest.h clientFriendRequest.c
	$(CFLAGS) -c clientFriendRequest.c -o clientFriendRequest.o $(GUI)

clientLogin.o: clientLogin.h clientLogin.c clientHome.h clientRegister.h clientRecoverPassword.h
	$(CFLAGS) -c clientLogin.c -o clientLogin.o $(GUI) 

clientRegister.o: clientRegister.h clientRegister.c clientDataStruct.h
	$(CFLAGS) -c clientRegister.c -o clientRegister.o $(GUI)

clientSettings.o: clientSettings.h clientSettings.c
	$(CFLAGS) -c clientSettings.c -o clientSettings.o $(GUI) 

clientChat.o: clientChat.h clientChat.c clientDataStruct.h
	$(CFLAGS) -c clientChat.c -o clientChat.o $(GUI) 

clientResetPassword.o: clientResetPassword.h clientResetPassword.c
	$(CFLAGS) -c clientResetPassword.c -o clientResetPassword.o $(GUI)

clientRecoverPassword.o: clientRecoverPassword.h clientRecoverPassword.c
	$(CFLAGS) -c clientRecoverPassword.c -o clientRecoverPassword.o $(GUI)

clientDataStruct.o: clientDataStruct.c clientDataStruct.h
	$(CFLAGS) -c clientDataStruct.c -o clientDataStruct.o $(GUI)

clientAddFriend.o: clientAddFriend.c clientAddFriend.h clientDataStruct.h
	$(CFLAGS) -c clientAddFriend.c -o clientAddFriend.o $(GUI)

#.o server

serverMain.o: serverMain.c serverLogin.h serverDataStruct.h serverChat.h serverHome.h serverAddFriend.h
	$(CFLAGS) -c serverMain.c -o serverMain.o

serverDataStruct.o: serverDataStruct.c serverDataStruct.h
	$(CFLAGS) -c serverDataStruct.c -o serverDataStruct.o

serverLogin.o: serverLogin.c serverLogin.h serverDataStruct.h
	$(CFLAGS) -c serverLogin.c -o serverLogin.o 

serverChat.o: serverChat.c serverChat.h serverDataStruct.h
	$(CFLAGS) -c serverChat.c -o serverChat.o

serverHome.o: serverHome.c serverHome.h serverDataStruct.h
	$(CFLAGS) -c serverHome.c -o serverHome.o

serverFriendRequest.o: serverFriendRequest.c serverFriendRequest.h serverDataStruct.h
	$(CFLAGS) -c serverFriendRequest.c -o serverFriendRequest.o 

serverAddFriend.o: serverAddFriend.c serverAddFriend.h serverDataStruct.h
	$(CFLAGS) -c serverAddFriend.c -o serverAddFriend.o $(GUI)

serverResetPassword.o: serverResetPassword.c serverResetPassword.h serverDataStruct.h
	$(CFLAGS) -c serverResetPassword.c -o serverResetPassword.o 

serverRecoverPassword.o: serverRecoverPassword.c serverRecoverPassword.h serverDataStruct.h
	$(CFLAGS) -c serverRecoverPassword.c -o serverRecoverPassword.o

#test:
test-gui: chat
	cd ../bin; ./chat zuma 5555

test-server: server
	cd ../bin; ./server 9998

test-comm: testComm.o
	$(CFLAGS) testComm.o -o test-comm
	./test-comm zuma 5201
testComm.o: clientMain.c  clientDataStruct.h
	$(CFLAGS) -c clientMain.c -o testComm.o -DtestComm $(GUI)
 
serverDataTest.out:  serverDataTest.o
	$(CFLAGS) serverDataTest.o -o serverDataTest.out
serverDataTest.o: serverDataStruct.c serverDataStruct.h
	$(CFLAGS) -c serverDataStruct.c -o serverDataTest.o -DDEBUG

serverLoginTest.out: serverLogin.o serverDataStruct.o
	$(CFLAGS) serverLogin.o serverDataStruct.o -o serverLoginTest.out

serverChatTest.out: serverChatTest.o serverDataStruct.o
	$(CFLAGS) serverChatTest.o  serverDataStruct.o -o serverChatTest.out
serverChatTest.o: serverChat.c serverChat.h serverDataStruct.h
	$(CFLAGS) -c serverChat.c -o serverChatTest.o -DDEBUG

serverAddFriendTest.out: serverAddFriendTest.o serverDataStruct.o
	$(CFLAGS) serverAddFriendTest.o  serverDataStruct.o -o serverAddFriendTest.out
serverAddFriendTest.o: serverAddFriend.c serverAddFriend.h serverDataStruct.h
	$(CFLAGS) -c serverAddFriend.c -o serverAddFriendTest.o -DDEBUG

serverRecoverPWTest.out: serverRecoverPWTest.o serverDataStruct.o
	$(CFLAGS) serverRecoverPWTest.o  serverDataStruct.o -o serverRecoverPWTest.out

serverRecoverPWTest.o: serverRecoverPassword.c serverRecoverPassword.h serverDataStruct.h
	 $(CFLAGS) -c serverRecoverPassword.c -o serverRecoverPWTest.o -DDEBUG

#test client
clientLoginTest.out: clientLoginTest.o clientHome.o
	$(CFLAGS) clientLoginTest.o clientHome.o -o clientLoginTest.out $(GUI)
clientLoginTest.o: clientLogin.h clientLogin.c clientHome.h
	$(CFLAGS) -c clientLogin.c -o clientLoginTest.o $(GUI) -DDEBUG

clientChatTest.out: clientChatTest.o clientDataStruct.o
	$(CFLAGS) clientChatTest.o clientDataStruct.o -o clientChatTest.out $(GUI)
clientChatTest.o: clientChat.h clientChat.c clientDataStruct.h
	$(CFLAGS) -c clientChat.c -o clientChatTest.o $(GUI) -DDEBUG -g

clientHomeTest.out: clientHomeTest.o clientDataStruct.o
	$(CFLAGS) clientHomeTest.o clientDataStruct.o -o clientHomeTest.out $(GUI)
 
clientHomeTest.o: clientHome.h clientHome.c clientDataStruct.h
	$(CFLAGS) -c clientHome.c -o clientHomeTest.o $(GUI) -DDEBUG

clientRegisterTest.out: clientRegisterTest.o clientDataStruct.o
	$(CFLAGS) clientRegisterTest.o clientDataStruct.o -o clientRegisterTest.out $(GUI)

clientRegisterTest.o: clientRegister.h clientRegister.c
	$(CFLAGS) -c clientRegister.c -o clientRegisterTest.o $(GUI) -DDEBUG

clientAddFriendTest.out: clientAddFriendTest.o clientDataStruct.o
	$(CFLAGS) clientAddFriendTest.o clientDataStruct.o -o clientAddFriendTest.out $(GUI)

clientAddFriendTest.o: clientAddFriend.h clientAddFriend.c
	$(CFLAGS) -c clientAddFriend.c -o clientAddFriendTest.o $(GUI) -DDEBUG

clientSettingsTest.out: clientSettingsTest.o clientDataStruct.o
	 $(CFLAGS) clientSettingsTest.o  clientDataStruct.o -o clientSettingsTest.out $(GUI)

clientSettingsTest.o: clientSettings.h clientSettings.c 
	$(CFLAGS) -c clientSettings.c -o clientSettingsTest.o $(GUI) -DDEBUG

clientRecoverPWTest.out: clientRecoverPWTest.o clientDataStruct.o
	 $(CFLAGS) clientRecoverPWTest.o  clientDataStruct.o -o clientRecoverPWTest.out $(GUI)

clientRecoverPWTest.o: clientRecoverPassword.h clientRecoverPassword.c
	$(CFLAGS) -c clientRecoverPassword.c -o clientRecoverPWTest.o $(GUI) -DDEBUG

clientResetPWTest.out: clientResetPWTest.o clientDataStruct.o
	$(CFLAGS) clientResetPWTest.o  clientDataStruct.o -o clientResetPWTest.out $(GUI)

clientResetPWTest.o: clientResetPassword.h clientResetPassword.c
	$(CFLAGS) -c clientResetPassword.c -o clientResetPWTest.o $(GUI) -DDEBUG

#EOF
