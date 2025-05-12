#include <iostream>
#include <Map>
#include <string>

class AuthCodeManager{
    private Map<string, pair<int, int>> AuthCodeManager;

    public boolean validateAuthCode(string authCode){
        return false;
    }

    public int getBeverageId(string authCode){
        return 0;
    }

    public void saveAuthCode(string authCode){

    }

    public string generateAuthCode(){
        return "";
    }
}