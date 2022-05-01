#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Customer.h";
#include "Card.h";
#include "Bank.h";


using namespace std;

class ServiceOperations {

public:  void readCustomers();													 // Read the customer text file and create customer objects in customer vector.
		 void readCards();														//  Read the card text file and create cards objects in cards vector.
		 void readBanks();														//  Read the bank text file and create banks objects in banks vector.
		 void updateAmount(Card &card,float transferBalance);
		 bool checkLogin(string name, string surname, string password);
		 bool checkReceiver(string name, string surname, string cardNumber);
		 void findCustomerCard(Customer &nCustomer);
		 void findCardBank(Card &nCard);
		 ServiceOperations();                                                                                                                                                                             
		 Customer loginCustomer;
		 Card receiverCard;
		 vector <Customer> customers;
		 vector <Card> cards;
		 vector <Bank> banks;
};