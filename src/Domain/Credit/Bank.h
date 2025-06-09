#pragma once
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "CreditCard.h"
#include "Exception/CustomException.h"

using namespace std;
namespace fs = std::filesystem;

class Bank {
private:
    list<CreditCard> cards;

public:
    Bank() = default;
    ~Bank() {
        for (CreditCard& card : cards) {
            delete &card;  
        }
        cards.clear();
    };
    virtual CreditCard* requestCard(string cardNumber);
    virtual void saveCreditCard(CreditCard creditCard);
};