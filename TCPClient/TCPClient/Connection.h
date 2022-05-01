#pragma once
#include <iostream>
#include <winsock2.h>

using namespace std;

class Connection {

public:	

	
	WSADATA wsd;
    int myClientSocket;
	void initializeSocket();
	void sendMessage(char* message);
	string receiveMessage();

};