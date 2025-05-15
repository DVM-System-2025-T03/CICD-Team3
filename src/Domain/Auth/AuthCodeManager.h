#pragma once
#include <string>
#include <map>
using namespace std;

class AuthCodeManager {
private:
    map<string, pair<int, int>> authCodeMap;

public:
    bool validateAuthCode(string authCode);
    int getBeverageId(string authCode);
    void saveAuthCode(string authCode, pair<int, int> beverage);
    string generateAuthCode();
};