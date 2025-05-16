#pragma once
#include <string>

#include "../../Domain/Credit/CreditCard.h"
#include "../../Domain/Credit/Bank.h"
#include "../../Domain/Socket/SocketManager.h"
#include "../../Domain/Auth/AuthCodeManager.h"

using namespace std;

class RequestPrePaymentController {
private:
    AuthCodeManager* authCodeManager;
    Bank* bank;
    SocketManager* socketManager;

public:
    RequestPrePaymentController(AuthCodeManager* authCodeManager, Bank* bank, SocketManager* socketManager);
    void enterPrePayIntention(bool intention);
    string enterCardNumber(string cardNumber, Beverage beverage, int quantity, int srcId, int dstId);
};