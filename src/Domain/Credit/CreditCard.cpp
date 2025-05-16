#include "CreditCard.h"
#include "exception/CustomException.h"
using namespace customException;

bool CreditCard::validateBalance(int price) {
    if (this->balance < price) {
        throw NotEnoughBalanceException("Not enough balance");
    }
    return true;
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

