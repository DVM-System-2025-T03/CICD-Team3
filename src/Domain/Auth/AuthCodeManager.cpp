#include "AuthCodeManager.h"
#include "exception/CustomException.h"

using namespace customException;

bool AuthCodeManager::validateAuthCode(string authCode) {
    if(authCodeMap.find(authCode) == authCodeMap.end()){
        throw NotFoundException("Auth code not found");
    }
    return true;
}

int AuthCodeManager::getBeverageId(string authCode) {
    map<string, pair<int, int>>::iterator auth = authCodeMap.find(authCode);
    
    if(auth == authCodeMap.end()){
        throw NotFoundException("Auth code not found");
    }

    return auth->second.first;
}

void AuthCodeManager::saveAuthCode(string authCode, pair<int, int> beverage) {
    authCodeMap[authCode] = beverage;
}

string AuthCodeManager::generateAuthCode() {
    const string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string authCode = "";

    for (int i = 0; i < 5; ++i) {
        authCode += CHARACTERS[rand() % CHARACTERS.length()];
    }
    return authCode;
}