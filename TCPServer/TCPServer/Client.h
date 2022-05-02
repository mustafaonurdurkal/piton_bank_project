#pragma once
#include <iostream>
#include <string>

#include "Card.h"
#include "Customer.h"

using namespace std;


class Client {

public:
	int socket;
	int receiveCount;
	int receiveCount2;

	bool girisyapildi;
	bool bakiyeyollandi ;
	bool secimyapildi;
	bool receiverVerify ;
	bool paraYatirma ;
	bool paraCekme ;
	bool paraTransfer ;

	string name;
	string surname;
	string password;
	string balance;
	string receiverName;
	string receiverSurname;
	string receiverCardnumber;

	Card card;
	Customer customer;
	Card receiverCard;
	Client();

};
