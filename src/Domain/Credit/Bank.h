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
    CreditCard* requestCard(string cardNumber);
    void saveCreditCard(CreditCard creditCard);
};