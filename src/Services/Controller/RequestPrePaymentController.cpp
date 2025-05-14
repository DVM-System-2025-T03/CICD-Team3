#include "RequestPrePaymentController.h"

RequestPrePaymentController::RequestPrePaymentController(AuthCodeManager* authCodeManager, Bank* bank, SocketManager* socketManager)
    : authCodeManager(authCodeManager), bank(bank), socketManager(socketManager) {}

bool RequestPrePaymentController::enterPrePayIntention(bool intention, Beverage beverage, int quantity, int srcId, int dstId) {
    if (!intention) {
        // uc1
        return false;
    }

    for (int i = 0; i < 3; i++) {
        string cardNumber;
        cout << "카드 번호를 입력하세요 현재 " << i + 1 << " : ";
        cin >> cardNumber;
        cout << "CARD NUMBER" << cardNumber << endl;
        CreditCard* card = bank->requestCard(cardNumber);
        if (!card || !card->isValid()) {
            continue;
        }

        if (!card->validateBalance(beverage.getPrice() * quantity)) {
            return false;
        }

        string authCode = authCodeManager->generateAuthCode();
        if (!socketManager->requestPrePayment(beverage.getId(), quantity, authCode, srcId, dstId)) {
            return false;
        }

        cout << "선결제 완료" << endl;
        cout << "인증 코드 : " << authCode << endl;

        return true;
    }
    cout << "카드번호 3회 실패" << endl;
    // uc1
    return false;
}

string RequestPrePaymentController::enterCardNumber(string cardNumber) {
    return "";
}