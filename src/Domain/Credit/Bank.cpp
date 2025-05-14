#include "Bank.h"
#include "CreditCard.h"

CreditCard* Bank::requestCard(string cardNumber) {
    return new CreditCard();
}

void Bank::saveCreditCard(CreditCard creditCard) {
    cards.push_back(creditCard);
}