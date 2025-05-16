#include "EnterAuthCodeController.h"
#include "exception/CustomException.h"
using namespace customException;

EnterAuthCodeController::EnterAuthCodeController(BeverageManager* beverageManager, AuthCodeManager* authCodeManager)
    : beverageManager(beverageManager), authCodeManager(authCodeManager) {
}

Beverage EnterAuthCodeController::enterAuthCode(string authCode) {
    bool isValid = false;

    for(int i = 0; i < 3; i++){
        isValid = authCodeManager->validateAuthCode(authCode);
        if(isValid) break;
    }

    if(!isValid){
        // uc 1
        throw InvalidException("Invalid auth code");
    }

    int beverageId = authCodeManager->getBeverageId(authCode);
    Beverage beverage = beverageManager->getBeverage(beverageId);
    return beverage;
}