#pragma once
#include <string>
using namespace std;

class CreditCard {
private:
    string cardNumber;
    int balance;

public:
    bool validateBalance(int price);
    void reduceBalance(int price);
};