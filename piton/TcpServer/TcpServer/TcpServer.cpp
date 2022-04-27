// TcpServer.cpp: Uygulamanın giriş noktasını tanımlar.
//

#include "TcpServer.h"
#include "Customer.h"
#include "ServiceOperations.h"
#include "Card.h";

using namespace std;


int main()
{
	

	ServiceOperations s = ServiceOperations();
	
	s.readCustomers();
	s.readCards();
	s.readBanks();
	cout << s.banks[1].bankName << s.banks[0].id;
	Card card;
	card.id = "001";
	card.cardBalance = "1473.25";
	s.updateAmount(card, 23.75f);
	

	return 0;
}
