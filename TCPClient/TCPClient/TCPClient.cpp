// TcpClient.cpp: Uygulamanın giriş noktasını tanımlar.
//

#include "TcpClient.h"
#include <iostream>
#include <winsock2.h>


using namespace std;

int main()
{
	int mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	cout << "PITON-BANK" << endl;
	cout << "LUTFEN  ADINIZI GIRINIZ = ";
	string isim;
	cin >> isim;
	cout << isim;
	return 0;
}

