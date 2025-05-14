#include "AuthCodeManager.h"

bool AuthCodeManager::validateAuthCode(string authCode) {
    if(authCodeMap.find(authCode) == authCodeMap.end()){
        return false;
    }
    return true;
}

int AuthCodeManager::getBeverageId(string authCode) {
    map<string, pair<int, int>>::iterator auth = authCodeMap.find(authCode);
    
    if(auth == authCodeMap.end()){
        return -1;
    }

    return auth->second.first;
}

void AuthCodeManager::saveAuthCode(string authCode) {
    
}

string AuthCodeManager::generateAuthCode() {
    return "";
}