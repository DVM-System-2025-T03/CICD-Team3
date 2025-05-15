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
    
}

bool CreditCard::isValid(){
    return !this->cardNumber.empty();
}