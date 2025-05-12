#include "RequestPrePaymentController.h"

void RequestPrePaymentController::enterPrePayIntention(bool intention, Beverage beverage, int quantity) {
    if(!intention){
        // uc1
        return;
    }

    for (int i = 0; i < 3; i++){
        string cardNumber;
        cout<<"카드 번호를 입력하세요 현재 "<< i+1 << " : ";
        cin>> cardNumber;

        card = bank.requestCard(cardNumber);
        if(card.isNull()){
            continue;
        }

        if(!card.validateBalance(beverage.getPrice() * quantity)){
            return;
        }

        string authCode = authCodeManager.generateAuthCode();
        if(!socketManager.requestPrePayment(beverage.getId(), quantity, authCode)){

        }

        cout<<"선결제 완료"<<endl;
        cout<<"인증 코드 : " << authCode<<endl;
        return; 
    }
    cout<<"카드번호 3회 실패"<<endl;
    // uc1
    return;
}

string RequestPrePaymentController::enterCardNumber(string cardNumber) {
    return "";
}