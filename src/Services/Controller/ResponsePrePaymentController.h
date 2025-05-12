#pragma once
#include "BeverageManager.h"
#include "AuthCodeManager.h"
#include "ResponsePrePaymentDTO.h"
#include "AuthCode.h"

class ResponsePrePaymentController {
private:
    BeverageManager beverageManager;
    AuthCodeManager authCodeManager;

public:
    ResponsePrePaymentDTO responsePrePay(int beverageId, int quantity, AuthCode authCode);
};