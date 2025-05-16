#include "Bank.h"
#include "CreditCard.h"

CreditCard* Bank::requestCard(string cardNumber) {
    for (auto& card : cards) {
        if (card.getCardNumber() == cardNumber && card.isValid()) {
            return &card;
        }
    }
    return nullptr;
}

void Bank::saveCreditCard(CreditCard creditCard) {
    for (auto& card : cards) {
        if (card.getCardNumber() == creditCard.getCardNumber()) {
            card = creditCard;      // 기존 카드 정보 업데이트
            return;
        }
    }
    cards.push_back(creditCard);    // 새로운 카드 정보 추가
}
