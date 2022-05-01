// TcpServer.cpp: Uygulamanın giriş noktasını tanımlar.

#pragma once
#include <winsock2.h>
#include "TcpServer.h"
#include "Customer.h"
#include "ServiceOperations.h"
#include "Card.h";

#include "Connection.h"


int main()
{   
	Connection connection;
	connection.initializeSocket();
	connection.selectFunction();
 

	return 0;
}
