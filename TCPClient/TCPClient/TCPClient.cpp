// TcpClient.cpp: Uygulamanın giriş noktasını tanımlar.
//
#pragma warning(disable : 4996)
#include "TcpClient.h"
#include <iostream>
#include <winsock2.h>
#include "Connection.h"
#include <string>

using namespace std;

#define PORT 9909


struct sockaddr_in clientInfo;
Connection connection;
char  custName[255];
char  custSurName[255];
char  custPassword[255];
char  receiverName[255];
char  receiverSurName[255];
char  receiverCardNumber[255];
char  bakiye[255];
char  buffer[256 + 1] = { 0, };

void BakiyeYatir() {
	system("cls");
	cout << "\t\t\t\n\nLutfen Yatirmak istenen tutari giriniz : ";
	cin >> bakiye;
	Sleep(100);
	send(connection.myClientSocket, bakiye, 255, 0);
	Sleep(100);
	recv(connection.myClientSocket, buffer, 256, 0);
	cout << "\t\t\t\nGuncel Bakiyeniz : " << buffer <<"\n\t\t\tAna menuye donuluyor...";
	Sleep(2000);
}
void BakiyeCek() {
	system("cls");
	cout << "\t\t\t\n\nLutfen Para cekmek istenen tutari giriniz : ";
	cin >> bakiye;
	Sleep(100);
	send(connection.myClientSocket, bakiye, 255, 0);
	Sleep(100);
	recv(connection.myClientSocket, buffer, 256, 0);
	if (buffer[0] == 'x') {
		//Yetersiz Bakiye
		cout << "\n\t\t\tBakiyeniz Yetersiz Lutfen Tekrar Deneyiniz";
		Sleep(1000);
		BakiyeCek();
	}
	else {
		cout << "\t\t\t\nGuncel Bakiyeniz : " << buffer<<"\nAnamenuye donuluyor.";
		Sleep(2000);
	}
	
}
void HavaleYap () {

	system("cls");
	cout << "\t\t\t\n\nHavale yapilmasi  istenen Kisinin bilgilerini giriniz : ";
	cout << "\t\t\t\n\nKisi adi : ";
	cin >> receiverName;
	cout << "\t\t\t\n\nKisi soyadi: ";
	cin >> receiverSurName;
	cout << "\t\t\t\n\nKart Numarasi: ";
	cin >> receiverCardNumber;

	send(connection.myClientSocket, receiverName, 255, 0);
	Sleep(100);
	send(connection.myClientSocket, receiverSurName, 255, 0);
	Sleep(100);
	send(connection.myClientSocket, receiverCardNumber, 255, 0);
	Sleep(100);
	recv(connection.myClientSocket, buffer, 256, 0);
	Sleep(100);

	if (buffer[0] == '0') {
		//Tranfer yapilacak card bulunamadi
		cout << endl << endl << "Hatali Giris Yaptiniz Lutfen tekrar deneyin...";
		Sleep(2000);
		HavaleYap();
	}
	else {
		//Transfer yapilacak card bulundu
		cout << endl << endl << "Lutfen transfer yapmak istediginiz para miktarini giriniz :";
		cin >> bakiye;
		send(connection.myClientSocket, bakiye, 255, 0);
		Sleep(100);
		recv(connection.myClientSocket, buffer, 255, 0);
		Sleep(100);

		if (buffer[0] == 'Y') {
			cout << "\t\t\t\nBakiyeniz Yetersiz...Lutfen Tekrar Deneyiniz";
			Sleep(1000);
			HavaleYap();
		}
		else {
			cout << "\t\t\t\nGuncel Bakiyeniz : " << buffer;
		}
		
	}
}
void AccountPage() {
	system("cls");
	string option;
	
	cout << " \t\t\t\t\t\tHOSGELDINIZ SAYIN  " << custName << " " << custSurName<<"\n\n\n";
	Sleep(100);
	send(connection.myClientSocket, "Kullanici giris yapti", 22, 0);
	Sleep(100);
	recv(connection.myClientSocket, buffer, 256, 0);
	Sleep(100);


	cout << "\t\t\t\t\t\t Kalan Bakiyeniz :" << buffer  <<"TL\n\n\n";
	cout << "\t\t\tLutfen Yapmak istediginiz islemi Seciniz\n\n";
	cout << "\t\t\t1-Bakiye Yatir\n";
	cout << "\t\t\t2-Bakiye Cek\n";
	cout << "\t\t\t3-Para Transferi Yap\n";
	cout << "\t\t\tLutfen Seciminizi yapiniz : ";
	cin >> option;
	int num = stoi(option);
	switch (num) {
	case 1:
		// Bakiye yatir
		send(connection.myClientSocket, "y", 2, 0);
		BakiyeYatir();	
		AccountPage();
		break;
	case 2:
		// Bakiye cek
		send(connection.myClientSocket, "c", 2, 0);
		BakiyeCek();
		AccountPage();
		break;
	case 3:
		// Havale yap
		send(connection.myClientSocket, "t", 2, 0);
		HavaleYap();

		break;
	default:
		// hatali giris tekrar secim ekranina yonlendir
		break;
	}
}
void initializePage() {
	cout << " \t\t\t\t\t+-+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+ +-+-+-+-+\n";
	cout << " \t\t\t\t\t|W|E|L|C|O|M|E| |T|O| |P|I|T|O|N| |B|A|N|K|\n";
	cout << " \t\t\t\t\t+-+-+-+-+-+-+-+ +-+-+ +-+-+-+-+-+ +-+-+-+-+\n\n\n\n\n";
	cout << "       \t\t\t\t\t\tLUTFEN GIRIS YAPINIZ\n\n";
	cout << "       \t\t\t\tISIM  :  ";
	cin >> custName;
	cout << "       \t\t\t\tSOYISIM  :  ";
	cin >> custSurName;
	cout << "       \t\t\t\tSIFRE : ";
	cin >> custPassword;

	

	Sleep(100);
	send(connection.myClientSocket, custName, 255, 0);
	Sleep(100);
	send(connection.myClientSocket, custSurName, 255, 0);
	Sleep(100);
	send(connection.myClientSocket, custPassword, 255, 0);
	Sleep(100);
	recv(connection.myClientSocket, buffer, 256, 0);
	Sleep(100);

	if (buffer[0] == '0') {
		//Yeni Sayfaya yonlendir giris  yapildi
		system("cls");
		initializePage();
	}
	else {
		//Sayfayi yenile yeniden giris bilgilerini cagir
		AccountPage();
	}

}
int main()
{
	connection.initializeSocket();
	initializePage();
	while (1);
	return 0;
}

