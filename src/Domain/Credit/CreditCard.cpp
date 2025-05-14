#include "CreditCard.h"

bool CreditCard::validateBalance(int price) {
    return false;
}

void CreditCard::reduceBalance(int price) {
    
}

bool CreditCard::isValid(){
    return !this->cardNumber.empty();
}