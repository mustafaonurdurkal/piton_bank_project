#pragma once
#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

class Card {
 
public: 
	    string id = "";
		string cardNumber = "";
		string bankid="";
		string cardCustomerName = "";
		string cardCustomerSurname = "";
	    string securityCode = "";
		string expirationDate = "";
	    string cardBalance;
		Bank bank;
		Card();

}; 
