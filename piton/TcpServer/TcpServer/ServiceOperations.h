#pragma once
#include <iostream>
#include <string>
#include "Customer.h";
#include "Card.h";
#include "Bank.h";
#include <vector>

using namespace std;

class ServiceOperations {

public:  void readCustomers();													 // Read the customer text file and create customer objects in customer vector.
		 void readCards();														//  Read the card text file and create cards objects in cards vector.
		 void readBanks();														//  Read the bank text file and create banks objects in banks vector.
		 void updateAmount(Card card,float transferBalance);
		 vector <Customer> customers;
		 vector <Card> cards;
		 vector <Bank> banks;
};