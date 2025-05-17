#include "RequestPrePaymentController.h"
#include "Exception/CustomException.h"
using namespace customException;
RequestPrePaymentController::RequestPrePaymentController(AuthCodeManager* authCodeManager, Bank* bank, SocketManager* socketManager, BeverageManager* beverageManager)
    : authCodeManager(authCodeManager), bank(bank), socketManager(socketManager), beverageManager(beverageManager) {}

void RequestPrePaymentController::enterPrePayIntention(bool intention) {
    if (!intention) {
        // uc1
        throw InvalidException("Invalid intention");
    }
    cout << "선결제 의사를 확인했습니다." << endl;
    cout << "선결제를 진행합니다." << endl;
}

string RequestPrePaymentController::enterCardNumber(string cardNumber, Beverage beverage, int quantity, int srcId, int dstId) {
    for (int i = 0; i < 3; i++) {
        string cardNumber;
        cout << "카드 번호를 입력하세요 현재 " << i + 1 << " : ";
        cin >> cardNumber;
        cout << "CARD NUMBER" << cardNumber << endl;
        try{
            CreditCard* card = bank->requestCard(cardNumber);
            if (!card || !card->isValid()) {
                continue;
            }

            bool isPayable = card->validateBalance(beverage.getPrice() * quantity);
            if (!isPayable) {
                throw NotEnoughStockException("Not enough balance");
            }

            string authCode = authCodeManager->generateAuthCode();
            
            bool isPrePayable = socketManager->requestPrePayment(beverage.getId(), quantity, authCode, srcId, dstId);
            if (!isPrePayable) {
                throw FailedToPrePaymentException("Invalid auth code");
            }
    
            cout << "선결제 완료" << endl;
            cout << "인증 코드 : " << authCode << endl;
            return authCode;
        }catch (const InvalidException& e) {
            cout << "카드번호가 유효하지 않습니다. 다시 입력하세요." << endl;
            continue;
        }catch (const NotEnoughStockException& e) {
            cout << "재고가 부족합니다. 다른 음료를 선택하세요." << endl;
            continue;
        }catch (const FailedToPrePaymentException& e) {
            cout << "선결제 실패. 다시 시도하세요." << endl;
            continue;
        }
    }
    cout << "카드번호 3회 실패" << endl;
    // uc1
    throw InvalidException("Invalid card number");
}