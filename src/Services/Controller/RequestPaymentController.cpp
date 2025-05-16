#include "RequestPaymentController.h"

RequestPaymentController::RequestPaymentController(BeverageManager* beverageManager, 
                                                       Bank* bank,
                                                       CreditCard* creditCard,
                                                       int beverageId,
                                                       int quantity,
                                                       int price)
    : beverageManager(beverageManager), bank(bank), creditCard(creditCard), 
      beverageId(beverageId), quantity(quantity), price(price) {}

Beverage RequestPaymentController::enterCardNumber(string cardNumber) {
    const int MAX_ATTEMPTS = 3;
    CreditCard* card = nullptr;

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
        card = bank->requestCard(cardNumber);
        if (card != nullptr) {
            break;
        }

        if (attempt < MAX_ATTEMPTS) {
            cerr << "[" << attempt << "번 실패] 올바르지 않은 카드번호입니다. 다시 입력해주세요: ";
            cin >> cardNumber;
        }
    }

    // 카드 조회를 3회 모두 실패한 경우
    if (card == nullptr) {
        throw CardNotFoundException();
    }

    // 잔액 검증
    bool isPayable = card->validateBalance(price);
    if (!isPayable) {
        throw InsufficientBalanceException();
    }

    // 재고 차감
    if (!beverageManager->reduceQuantity(beverageId, quantity)) {
        throw BeverageReductionException();
    }

    // 결제 처리
    card->reduceBalance(price);
    bank->saveCreditCard(*card);

    // 구매한 음료 반환
    return beverageManager->getBeverage(beverageId);
}