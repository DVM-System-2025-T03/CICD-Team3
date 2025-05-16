#pragma once
#include "../../Domain/Beverage/BeverageManager.h"
#include "../../Domain/Auth/AuthCodeManager.h"
#include "../../Domain/DTO/ResponsePrePaymentDTO.h"
#include "../../Domain/Auth/AuthCode.h"

class ResponsePrePaymentController {
    private:
        BeverageManager beverageManager;
        AuthCodeManager authCodeManager;

    public:
        ResponsePrePaymentDTO responsePrePay(int beverageId, int quantity, string authCode);
};

