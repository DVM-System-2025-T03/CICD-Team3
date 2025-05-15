#pragma once
#include <string>
using namespace std;

class CreditCard {
private:
    string cardNumber;
    int balance;

public:
    CreditCard(string cardNumber, int balance) : cardNumber(cardNumber), balance(balance) {} // Default balance for testing
    bool validateBalance(int price);
    void reduceBalance(int price);
    bool isValid();
};