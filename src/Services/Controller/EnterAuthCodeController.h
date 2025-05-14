#pragma once
#include <string>
#include <optional>
#include "../../Domain/Beverage/BeverageManager.h"
#include "../../Domain/Auth/AuthCodeManager.h"
#include "../../Domain/Beverage/Beverage.h"
using namespace std;

class EnterAuthCodeController {
private:
    BeverageManager* beverageManager;
    AuthCodeManager* authCodeManager;

public:
    EnterAuthCodeController(BeverageManager* beverageManager, AuthCodeManager* authCodeManager);
    optional<Beverage> enterAuthCode(string authCode);
};