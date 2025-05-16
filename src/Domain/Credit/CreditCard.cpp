#include "CreditCard.h"

bool CreditCard::validateBalance(int price) {
    return balance >= price;
}

void CreditCard::reduceBalance(int price) {
    if (price < 0) {
        throw invalid_argument("Price cannot be negative");
    }

    if (balance < price) {
        throw out_of_range("Insufficient balance");
    }

    balance -= price;
}

bool CreditCard::isValid(){
    return !this->cardNumber.empty();
}
