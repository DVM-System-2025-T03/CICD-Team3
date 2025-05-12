#pragma once
#include <string>
#include "BeverageManager.h"
#include "Bank.h"
#include "CreditCard.h"
#include "Beverage.h"
using namespace std;

class RequestPaymentController {
private:
    BeverageManager beverageManager;
    Bank bank;
    CreditCard creditCard;

public:
    Beverage enterCardNumber(string cardNumber);
};