#pragma once
#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

class Card {

         
public: Card();
	    string id = "";
		string cardNumber = "";
		string bankid="";
		string cardCustomerName = "";
	    string securityCode = "";
		string expirationDate = "";
	    string cardBalance;

}; 
