#pragma once
#include "Connection.h"
#include <iostream>
#include <winsock2.h>
#include <string>
#include "ServiceOperations.h"

using namespace std;

#define PORT 9909
int clients[5];
ServiceOperations serviceOperation ;
char buffer[256 + 1] = { 0, };


void Connection::ProcessNewMessage(int clientSocket) {
	int k = 0;
	for (k = 0; k < sizeof(clientVector); k++)
	{
		if (clientVector[k].socket == clientSocket) {
			 break;
		}
	}
	cout << endl<<"Soket " << clientSocket << "den gelen yeni mesaj isleniyor";

	int nRet = recv(clientSocket, buffer, 256, 0);

	//Kullanici programi kapatti...
	if (nRet < 0) {													
		cout<<endl << "Biseyler ters gitti baglanti kesiliyor.";   
		closesocket(clientSocket);
		clientVector[k].girisyapildi = false;
		clientVector[k].bakiyeyollandi = false;
		clientVector[k].secimyapildi = false;
		clientVector[k].receiveCount = 0;
		clientVector[k].receiveCount2 = 0;
		for (int index = 0; index < 5; index++)
		{
			if (clients[index] == clientSocket) {
				clients[index] = 0;
				break;
			}
		}
	}

	//Kullanici mesaj yollamaya devam ediyor
	else {															
		clientVector[k].receiveCount++;
		cout << endl << "Gelen Mesaj: " << buffer<<endl;

		//Kullanici giris yapmadi
		if (!clientVector[k].girisyapildi) {
			if (clientVector[k].receiveCount == 1) {
				clientVector[k].name = buffer;
			}
			else if (clientVector[k].receiveCount == 2) {
				clientVector[k].surname = buffer;

			}
			else if (clientVector[k].receiveCount == 3) {
				clientVector[k].password = buffer;
				serviceOperation.readCustomers();
				clientVector[k].girisyapildi = serviceOperation.checkLogin(clientVector[k].name, clientVector[k].surname, clientVector[k].password,clientVector[k].customer);
				if (clientVector[k].girisyapildi) {
					send(clientSocket, "1", 2, 0);	
				}
				else {
					send(clientSocket, "0", 2, 0);
				}   
				clientVector[k].receiveCount = 0;
				
			}

		}

		//Kullanici giris yapti
		else {					

			//Kullaniciya bakiye bilgisi yollaniyor...
			if (!clientVector[k].bakiyeyollandi) {
				serviceOperation.readCards();
				for (int i = 0; i < sizeof(serviceOperation.cards); i++)
				{
					cout << "\n\n\t\t "<< serviceOperation.cards[i].id<<"       "<<clientVector[k].customer.cardId;
					if (serviceOperation.cards[i].id == clientVector[k].customer.cardId) {
						
						clientVector[k].card = serviceOperation.cards[i];
						char* cstr = &clientVector[k].card.cardBalance[0];
						send(clientSocket, cstr, 256, 0);
						clientVector[k].bakiyeyollandi = true;
						break;
						
					}

				}
			}

			//Kullanici secim bilgisi belirleniyor...
			else if (!clientVector[k].secimyapildi) {
				clientVector[k].paraYatirma = (buffer[0] == 'y'); //secim para yatirmak ise
				clientVector[k].paraCekme = (buffer[0] == 'c');	//secim para cekmek ise
				clientVector[k].paraTransfer = (buffer[0] == 't');//secim para transfer ise
				clientVector[k].secimyapildi = true;
			}

			//Kullanici secimine gore operasyonlar yapiliyor
			else{												
				
				//Secim para yatirma ise
				if (clientVector[k].paraYatirma) {
					float income = stof(string(buffer));
					serviceOperation.updateAmount(clientVector[k].card, income);
					char* cstr = &clientVector[k].card.cardBalance[0];
					send(clientSocket, cstr, 256, 0);
					clientVector[k].paraYatirma = false;
					clientVector[k].bakiyeyollandi = false;
					clientVector[k].secimyapildi = false;
				}

				//Secim para cekme ise
				else if (clientVector[k].paraCekme) {
					float income = stof(string(buffer)); 
					float cardBalance = stof(string(clientVector[k].card.cardBalance));
					if (cardBalance < income) {
						send(clientSocket, "x", 2, 0);
					}
					else {
						serviceOperation.updateAmount(clientVector[k].card, income*(-1));
						char* cstr = &clientVector[k].card.cardBalance[0];
						send(clientSocket, cstr, 256, 0);
						clientVector[k].paraCekme = false;
						clientVector[k].bakiyeyollandi = false;
						clientVector[k].secimyapildi = false;
					}	
				}

				//Secim para transferi ise
				else if (clientVector[k].paraTransfer) {

					if (clientVector[k].receiveCount2 == 0) {
						clientVector[k].receiverName = buffer;
						clientVector[k].receiveCount2++;
					}
					else if (clientVector[k].receiveCount2 == 1) {
						clientVector[k].receiverSurname = buffer;
						clientVector[k].receiveCount2++;
					}
					else if (clientVector[k].receiveCount2 == 2) {
						clientVector[k].receiverCardnumber = buffer;
						serviceOperation.readCards();
						clientVector[k].receiverVerify = serviceOperation.checkReceiver(clientVector[k].receiverName, clientVector[k].receiverSurname, clientVector[k].receiverCardnumber);
						clientVector[k].receiveCount2++;
					}
				    if (clientVector[k].receiveCount2 == 3) {
						if (clientVector[k].receiverVerify) {
							send(clientSocket, "1", 2, 0);
							clientVector[k].receiveCount2++;
						}
						else {
							send(clientSocket, "0", 2, 0);
							clientVector[k].receiveCount2 = 0;
						}	
						
					}
					if (clientVector[k].receiveCount2 == 4) {
						serviceOperation.findCustomerCard(clientVector[k].customer);
						//Ayni banka ise
						if (clientVector[k].customer.card.bankid == serviceOperation.receiverCard.bankid) {
							clientVector[k].receiveCount2++;
						}
						//Farkli banka ise
						else {
							clientVector[k].receiveCount2+=2;
						}
					}
					//Ayni Banka transfer islemi
					else if (clientVector[k].receiveCount2 == 5) {
						float income = stof(string(buffer));
						float cardBalance = stof(string(clientVector[k].card.cardBalance));
						if (cardBalance < income) {
							send(clientSocket, "Y", 2, 0);
							clientVector[k].receiveCount2 = 0;
						}
						else {
							serviceOperation.updateAmount(clientVector[k].card, income * (-1));
							serviceOperation.updateAmount(serviceOperation.receiverCard, income);
							char* cstr = &clientVector[k].card.cardBalance[0];
							send(clientSocket, cstr, 256, 0);
						}
					}
					//Farkli Banka transfer islemi
					else if (clientVector[k].receiveCount2 == 6) {
						float income = stof(string(buffer));
						float cardBalance = stof(string(clientVector[k].card.cardBalance));
						if (cardBalance < income) {
							send(clientSocket, "Y", 2, 0);
							clientVector[k].receiveCount2 = 0;
						}
						else {
							serviceOperation.readBanks();
							serviceOperation.findCardBank(clientVector[k].card);
							int fee = (stof(string(clientVector[k].card.bank.fee)) * income)/100;
							serviceOperation.updateAmount(clientVector[k].card, (income + fee) * (-1) );
							serviceOperation.updateAmount(serviceOperation.receiverCard, income);
							char* cstr = &clientVector[k].card.cardBalance[0];
							send(clientSocket, cstr, 256, 0);
						}
					}
				}
			}
		}
	}
}

void Connection::ProcessTheNewRequest() {

	//new connection request
	if (FD_ISSET(mySocket, &fr)) {
		int len = sizeof(struct sockaddr);
		int clientSocket = accept(mySocket, NULL, &len);
		if (clientSocket > 0) {
			//Put it into the client fd_set
			int index;
			
			for (index = 0; index < 5; index++)
			{
				if (clients[index] == 0 ) {
					clients[index] = clientSocket;
					Client client;
					client.socket = clientSocket;
					clientVector.push_back(client);
					//cout << clientSocket;
					//cout<<endl << clients[index];
					//send(clientSocket, "Baglanti server tarafindan saglandi.", 37, 0);
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

void Connection::initializeSocket()
{
	int nRet = 0;

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

}

void Connection::selectFunction()
{	
	int nRet = 0;
	maxFd = mySocket;
	struct timeval timevalue;
	timevalue.tv_sec = 10;
	timevalue.tv_usec = 0;
	

	while (true) {
		FD_ZERO(&fr );
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
			// Process Reqeust 
			//cout << "Porta bir baglanti veya yeni mesaj geldi\n";
			ProcessTheNewRequest();


		}
		else if (nRet == 0) {
			//No connection or any communication reqeust made or your can say that none of the socket descriptor are ready
			
		}
		else {
			cout << "error on port";

			// failed an application
			//WSACleanup();
			//exit(EXIT_FAILURE);
		}

	}
}
