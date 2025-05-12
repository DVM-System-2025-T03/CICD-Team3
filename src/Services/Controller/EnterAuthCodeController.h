#pragma once
#include <string>
#include "BeverageManager.h"
#include "AuthCodeManager.h"
#include "Beverage.h"
using namespace std;

class EnterAuthCodeController {
private:
    BeverageManager beverageManager;
    AuthCodeManager authCodeManager;

public:
    Beverage enterAuthCode(string authCode);
};