#include "AuthCodeManager.h"

bool AuthCodeManager::validateAuthCode(string authCode) {
    return false;
}

int AuthCodeManager::getBeverageId(string authCode) {
    return 0;
}

void AuthCodeManager::saveAuthCode(int beverageId, int quantity, string authCode) {
    this->authCodeMap.insert({authCode, {beverageId, quantity}});
}

string AuthCodeManager::generateAuthCode() {
    return "";
}