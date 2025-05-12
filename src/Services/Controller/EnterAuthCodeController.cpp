#include "EnterAuthCodeController.h"

Beverage EnterAuthCodeController::enterAuthCode(string authCode) {
    bool isValid = false;

    for(int i = 0; i < 3; i++){
        isValid = authCodeManager.validateAuthCode(authCode);
        if(isValid) break;
    }

    if(!isValid){
        // uc 1
        return ;
    }

    int beverageId = authCodeManager.getBeverageId(authCode);
    Beverage beverage = beverageManager.getBeverage(beverageId);
    return beverage;
}