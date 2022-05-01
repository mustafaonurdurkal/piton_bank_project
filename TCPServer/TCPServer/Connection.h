#pragma once
#include <iostream>
#include <winsock2.h>
#include <vector>
#include "Client.h"

using namespace std;

class Connection {

public:

	struct sockaddr_in hostInfo;
	fd_set fr, fw, fe;
	int maxFd;
	int mySocket;
	WSADATA wsd;
	void initializeSocket();
	void selectFunction();
	void ProcessTheNewRequest();
	void ProcessNewMessage(int clientSocket);
	vector <Client> client;
};