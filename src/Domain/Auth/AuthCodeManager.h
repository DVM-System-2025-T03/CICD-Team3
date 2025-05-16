#pragma once
#include <string>
#include <map>
#include <random>
using namespace std;

class AuthCodeManager {
private:
    map<string, pair<int, int>> authCodeMap;

public:
    bool validateAuthCode(string authCode);
    int getBeverageId(string authCode);
    void saveAuthCode(int beverageId, int quantity, string authCode);
    string generateAuthCode();
};