#include "ResponsePrePaymentController.h"

ResponsePrePaymentDTO ResponsePrePaymentController::responsePrePay(int beverageId, int quantity, string authCode) {
    Beverage beverage = this->beverageManager.getBeverage(beverageId);

    bool isReduced = this->beverageManager.reduceQuantity(beverageId, quantity);

    if(isReduced){
        this->authCodeManager.saveAuthCode(beverageId, quantity, authCode);
    }
    
    ResponsePrePaymentDTO responsePrePaymentDTO(beverageId, quantity, isReduced);

    return responsePrePaymentDTO;
}