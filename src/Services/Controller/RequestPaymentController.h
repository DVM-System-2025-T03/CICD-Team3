#pragma once
#include <string>
#include "../../Domain/Beverage/BeverageManager.h"
#include "../../Domain/Credit/Bank.h"
#include "../../Domain/Credit/CreditCard.h"
#include "../../Domain/Beverage/Beverage.h"
using namespace std;

class RequestPaymentController {
private:
    BeverageManager beverageManager;
    Bank bank;
    CreditCard creditCard;

public:
    Beverage enterCardNumber(string cardNumber);
};