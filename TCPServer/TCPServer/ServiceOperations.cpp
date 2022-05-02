#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Customer.h";
#include "Card.h";
#include "ServiceOperations.h"

using namespace std;

void ServiceOperations::readCustomers()
{
    ifstream readFile;
    readFile.open("customer.txt");
	string row ;

    if (readFile.is_open()) {

        while (getline(readFile, row)) {
            int characterCounter = 0;
            
            Customer customer;
            for (int i = 0; i < row.length(); i++) {
               
                if (row[i] != '*') {
                    if (characterCounter == 0) {
                        customer.id += row[i];
                    }
                    if (characterCounter == 1 ) {
                        customer.customerName += row[i];
                    }
                    if (characterCounter == 2 ) {
                        customer.customerSurname += row[i];
                    }
                    if (characterCounter == 3 ) {
                        customer.customerPassword += row[i];
                    } 
                    if (characterCounter == 4) {
                        customer.cardId += row[i];
                    }
                }
                else { characterCounter++; };
            }
            customers.push_back(customer);
            //cout << row << endl;
        }

        readFile.close();
    }

   
}
void ServiceOperations::readCards()
{
    ifstream readFile;
    readFile.open("card.txt");
    string row;

    if (readFile.is_open()) {

        cards.clear();
        while (getline(readFile, row)) {
            int characterCounter = 0;

            Card card;
            for (int i = 0; i < row.length(); i++) {

                if (row[i] != '*') {

                    if (characterCounter == 0) {
                        card.id += row[i];
                    }
                    if (characterCounter == 1) {
                        card.cardNumber += row[i];
                    }
                    if (characterCounter == 2) {
                        card.bankid += row[i];
                    }
                    if (characterCounter == 3) {
                        card.cardCustomerName += row[i];
                    }
                    if (characterCounter == 4) {
                        card.cardCustomerSurname += row[i];
                    }
                    if (characterCounter == 5) {
                        card.expirationDate += row[i];
                    }
                    if (characterCounter == 6) {
                        card.securityCode += row[i];
                    }
                    if (characterCounter == 7) {
                        card.cardBalance += row[i];
                    }
                }
                else { characterCounter++; };
            }
            cards.push_back(card);
        }

        readFile.close();
    }

}
void ServiceOperations::readBanks()
{

    ifstream readFile;
    readFile.open("bank.txt");
    string row;

    if (readFile.is_open()) {

        while (getline(readFile, row)) {
            int characterCounter = 0;

            Bank bank;
            for (int i = 0; i < row.length(); i++) {

                if (row[i] != '*') {

                    if (characterCounter == 0) {
                        bank.bankName += row[i];
                    }
                    if (characterCounter == 1) {
                        bank.id += row[i];
                    }
                    if (characterCounter == 2) {
                        bank.fee += row[i];
                    }
                  
                }
                else { characterCounter++; };
            }
            banks.push_back(bank);
           // cout << row << endl;
        }

        readFile.close();
    }

}
void ServiceOperations::updateAmount(Card &card, float changeBalance)
{
       float oldBalance = 0.00f;
        oldBalance= stof(card.cardBalance);
        float newBalance = 0.00f;
        newBalance= oldBalance + changeBalance;
        
    for (int i = 0; i < cards.size(); i++) {

        if (card.id == cards[i].id) {
            cards[i].cardBalance = to_string(newBalance);
            card.cardBalance= to_string(newBalance);
        }
    }

    ofstream writeOnFile;
    writeOnFile.open("temp.txt");
    string str="";
    for (int i = 0; i < cards.size(); i++) {
       
        //if the last card element  so  no new line
        if (i == cards.size() - 1) {  
            str += cards[i].id + '*' + cards[i].cardNumber + '*' + cards[i].bankid + '*' + cards[i].cardCustomerName + '*'
                + cards[i].cardCustomerSurname + '*' + cards[i].expirationDate + '*' + cards[i].securityCode + '*' + cards[i].cardBalance ;
        }
        else {
            str += cards[i].id + '*' + cards[i].cardNumber + '*' + cards[i].bankid + '*' + cards[i].cardCustomerName + '*'
                + cards[i].cardCustomerSurname + '*' + cards[i].expirationDate + '*' + cards[i].securityCode + '*' + cards[i].cardBalance + '\n';
        }

    }
    writeOnFile << str;
    writeOnFile.close();
    remove("card.txt");
    rename("temp.txt", "card.txt");

    

}
bool ServiceOperations::checkLogin(string name, string surname,string password,Customer &clientCustomer)
{
    readCustomers();
    for (int i = 0; i < size(customers); i++)
    {
        if (name == customers[i].customerName && surname == customers[i].customerSurname && password == customers[i].customerPassword) {
            clientCustomer = customers[i];
            return true;
        }
    }


    return false;
}
bool ServiceOperations::checkReceiver(string name, string surname, string cardNumber, Card &clientReceiverCard)
{
    readCards();
    for (int i = 0; i < size(cards); i++)
    {
        if (name == cards[i].cardCustomerName && surname == cards[i].cardCustomerSurname && cardNumber == cards[i].cardNumber) {
            clientReceiverCard = cards[i];
            return true;
        }
    }

    return false;
}
void ServiceOperations::findCustomerCard(Customer &nCustomer)
{
    for (int i = 0; i < sizeof(cards); i++)
    {
        if (cards[i].id == nCustomer.cardId) {
            nCustomer.card = cards[i];
            break;
        }
    }
}
void ServiceOperations::findCardBank(Card &nCard)
{
    for (int i = 0; i < sizeof(banks); i++)
    {
        cout << "\ngirdim   " << i;
        if (banks[i].id == nCard.bankid) {
            cout << "\ngirdim2   " ;
            nCard.bank = banks[i];
            cout << "\ngirdim3   " << nCard.bank.id<<"\t"<<nCard.bank.fee;
            break;
        }
    }
}
ServiceOperations::ServiceOperations()
{

}


