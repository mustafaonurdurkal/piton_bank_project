#pragma warning(disable : 4996)
#include "Connection.h"
#include <iostream>
#include <winsock2.h>
#include <string>

using namespace std;

#define PORT 9909


void Connection::initializeSocket()
{
	int nRet = 0;
	struct sockaddr_in clientInfo;

	//Socket tanimlaniyor
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) < 0) {
		cout << "WSA BASLATILAMADI...";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else { cout << endl << "WSA BASLATILDI..."; }

	 myClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (myClientSocket < 0) {
		cout << endl << "Socket acilmadi";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else { cout << endl << "Socket Acildi...\n" << "Socket id= " << myClientSocket << '\n'; }

	//Veri yapisi olusturuluyor

	clientInfo.sin_family = AF_INET;
	clientInfo.sin_port = htons(PORT);
	clientInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(clientInfo.sin_zero), 0, 8);

	//Veri yapisi ile socket baglantisi saglaniyor
	nRet = connect(myClientSocket, (struct sockaddr*)&clientInfo, sizeof(struct sockaddr));
	if (nRet < 0) {
		cout << "Servera Baglanamadi";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else {
		cout << endl << myClientSocket;

	}
}

