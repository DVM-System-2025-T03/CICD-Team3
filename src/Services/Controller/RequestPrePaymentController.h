#pragma once
#include <string>
#include "AuthCodeManager.h"
#include "CreditCard.h"
#include "Bank.h"
#include "SocketManager.h"
using namespace std;

class RequestPrePaymentController {
private:
    AuthCodeManager authCodeManager;
    CreditCard card;
    Bank bank;
    SocketManager socketManager;

public:
    void enterPrePayIntention(bool intention, Beverage beverage, int quantity);
    string enterCardNumber(string cardNumber);
};