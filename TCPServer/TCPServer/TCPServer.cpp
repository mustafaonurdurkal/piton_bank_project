// TcpServer.cpp: Uygulamanın giriş noktasını tanımlar.


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

int main()
{   
	int nRet = 0;

	//Socket tanimlaniyor
	WSADATA wsd;                                      //Windows platformunda Socket programini destekleyen environment
	if (WSAStartup(MAKEWORD(2, 2), &wsd)<0) {
		cout << "WSA BASLATILAMADI...";
	}else{ cout << endl << "WSA BASLATILDI..."; }

	int mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket < 0) {
		cout << endl << "Socket acilmadi";
		exit(EXIT_FAILURE);
	}else{ cout << endl << "Socket Acildi...\n"<<"Socket id= "<<mySocket<< '\n'; }

	hostInfo.sin_family = AF_INET;
	hostInfo.sin_port = htons(PORT);
	hostInfo.sin_addr.s_addr  = INADDR_ANY;
	memset(&(hostInfo.sin_zero), 0, 8);



	// Socket Baglantisi
	nRet = bind(mySocket, (sockaddr*)&hostInfo, sizeof(sockaddr));
	if (nRet < 0) {
		cout << "Local Porta Baglanamadi";
		exit(EXIT_FAILURE);
	}else{ cout << "Local Porta Baglandi.\n"; }




	//Clienttan gelen istek dinleniyor.
	
	nRet = listen(mySocket, 5);
	if (nRet < 0) {
		cout << "Local Portu dinleme basarisiz";
		exit(EXIT_FAILURE);
	}
	else { cout << "Local Port Dinleniyor.\n"; }

	



	 //Select fonksiyonu  ile  tum  socketleri dinleriz

	maxFd = mySocket;
	struct timeval timevalue;
	timevalue.tv_sec = 1;
	timevalue.tv_usec = 0;
	
	FD_ZERO(&fr);
	FD_ZERO(&fw);
	FD_ZERO(&fe);
	FD_SET(mySocket, &fr);
	FD_SET(mySocket, &fe);
	
	cout << endl << "Before select call:" << fr.fd_count;

	nRet = select(maxFd+1, & fr ,&fw ,&fe ,&timevalue);

	if (nRet > 0) {
		//When someone connects or communicates with a message over a dedicated function
	}
	else if (nRet == 0) {
		//No connection or any communication requst made or your can say that none of the socket descriptor are ready
		cout << endl << "Nothing on port: " << PORT;
	}
	else {
		// failed an application
	}

	cout << endl << "After select call:" << fr.fd_count;



	/*ServiceOperations s = ServiceOperations();

	s.readCustomers();
	s.readCards();
	s.readBanks();
	cout << s.banks[1].bankName << s.banks[0].id;
	Card card;
	card.id = "001";
	card.cardBalance = "1803.25";
	s.updateAmount(card, 23.75f);*/


	return 0;
}
