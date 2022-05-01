#include <winsock2.h>
#include "TcpServer.h"
#include "Customer.h"
#include "ServiceOperations.h"
#include "Card.h";

#define PORT 9909

using namespace std;

struct sockaddr_in hostInfo;
fd_set fr, fw, fe;
int maxFd;
int mySocket;
int clients[5];

void ProcessNewMessage(int clientSocket) {
	cout << endl << "Clienttan gelen yeni mesaj isleniyor" << clientSocket;
	char buffer[256 + 1] = { 0, };
	int nRet = recv(clientSocket, buffer, 256, 0);
	if (nRet < 0) {
		cout << "Biseyler ters gitti baglanti kesiliyor.";
		closesocket(clientSocket);
		for (int index = 0; index < 5; index++)
		{
			if (clients[index] == clientSocket) {
				clients[index] = 0;
				break;
			}
		}
	}
	else {
		cout << endl << "The message receive from client is:" << buffer;
		// Clienta geri cevap yolla
		send(clientSocket, "Islem gerceklestiriliyor", 23, 0);
		cout << endl << "********************************";

	}
}


void ProcessTheNewRequest() {

	//new connection request
	if (FD_ISSET(mySocket, &fr)) {

		int len = sizeof(struct sockaddr);
		int clientSocket = accept(mySocket, NULL, &len);
		if (clientSocket > 0) {
			//Put it into the client fd_set
			int index;
			for (index = 0; index < 5; index++)
			{
				if (clients[index] == 0) {
					clients[index] = clientSocket;
					send(clientSocket, "Baglanti server tarafindan saglandi.", 37, 0);
					break;
				}

			}
			if (index == 5) {
				cout << endl << "client sirasi dolu...Yeni baglantiya acik degil.";
			}
		}
	}
	else {
		for (int index = 0; index < 5; index++)
		{
			if (FD_ISSET(clients[index], &fr)) {
				ProcessNewMessage(clients[index]);
			}
		}
	}
}

void contactWithClient()
{
	int nRet = 0;

	//Socket tanimlaniyor
	WSADATA wsd;                                      //Windows platformunda Socket programini destekleyen environment
	if (WSAStartup(MAKEWORD(2, 2), &wsd) < 0) {
		cout << "WSA BASLATILAMADI...";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else { cout << endl << "WSA BASLATILDI..."; }

	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket < 0) {
		cout << endl << "Socket acilmadi";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else { cout << endl << "Socket Acildi...\n" << "Socket id= " << mySocket << '\n'; }

	hostInfo.sin_family = AF_INET;
	hostInfo.sin_port = htons(PORT);
	hostInfo.sin_addr.s_addr = INADDR_ANY;
	memset(&(hostInfo.sin_zero), 0, 8);

	//Socket ayarlari yapilandiriliyor.
	int optVal = 0;
	int optLen = sizeof(optVal);
	nRet = setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optVal, optLen);
	if (!nRet) {
		cout << endl << "Socket ayarlari basari ile yapilandirildi.";
	}
	else {
		cout << endl << "Socket ayarlari yapilandirilamadi.";
		WSACleanup();
		exit(EXIT_FAILURE);
	}


	// Socket Baglantisi
	nRet = bind(mySocket, (struct sockaddr*)&hostInfo, sizeof(sockaddr));
	if (nRet < 0) {
		cout << "Local Porta Baglanamadi";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else { cout << endl << "Local Porta Baglandi.\n"; }




	//Clienttan gelen istek dinleniyor.

	nRet = listen(mySocket, 5);
	if (nRet < 0) {
		cout << "Local Portu dinleme basarisiz";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else { cout << "Local Port Dinleniyor.\n"; }





	//Select fonksiyonu  ile  tum  socketleri dinleriz

	maxFd = mySocket;
	struct timeval timevalue;
	timevalue.tv_sec = 1;
	timevalue.tv_usec = 0;

	while (true) {

		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);
		FD_SET(mySocket, &fr);
		FD_SET(mySocket, &fe);

		//set the clients
		for (int index = 0; index < 5; index++)
		{
			if (clients[index] != 0) {
				FD_SET(clients[index], &fr);
				FD_SET(clients[index], &fe);
			}
		}


		nRet = select(maxFd + 1, &fr, &fw, &fe, &timevalue);

		if (nRet > 0) {
			//When someone connects or communicates with a message over a dedicated function
			// Process Requst 
			ProcessTheNewRequest();

		}
		else if (nRet == 0) {
			//No connection or any communication requst made or your can say that none of the socket descriptor are ready

		}
		else {
			// failed an application
			WSACleanup();
			exit(EXIT_FAILURE);
		}

	}




