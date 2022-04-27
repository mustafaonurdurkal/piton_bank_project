#pragma once
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

class Customer {

public:	string id="";
		string customerSurname="";
		string customerPassword="";
	    string customerName="";
		string cardId = "";
		Customer(int receiveId);
		Customer();
};
