#include "Client.h"

Client::Client()
{
	socket = 0;
	receiveCount = 0;
	receiveCount2 = 0;

	girisyapildi = false;
	bakiyeyollandi = false;
	secimyapildi = false;
	receiverVerify = false;
	paraYatirma = false;
	paraCekme = false;
	paraTransfer = false;
}
