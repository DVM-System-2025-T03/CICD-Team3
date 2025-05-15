#include "Bank.h"
#include "CreditCard.h"

CreditCard* Bank::requestCard(string cardNumber) {
    // file을 읽어온다.
    int balance = 10000; // 예시로 10000으로 설정
    return new CreditCard(cardNumber, balance);
}

void Bank::saveCreditCard(CreditCard creditCard) {
    cards.push_back(creditCard);
}