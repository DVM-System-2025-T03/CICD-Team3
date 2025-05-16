#pragma once
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CreditCard.h"

using namespace std;

class Bank {
private:
    list<CreditCard> cards;

public:
    CreditCard* requestCard(string cardNumber);
    void saveCreditCard(CreditCard creditCard);
};