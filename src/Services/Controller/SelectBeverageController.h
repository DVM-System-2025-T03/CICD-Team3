#pragma once
#include "../../Domain/Location/LocationManager.h"
#include "../../Domain/Beverage/BeverageManager.h"
#include "../../Domain/Socket/SocketManager.h"

class SelectBeverageController {
private:
    LocationManager locationManager;
    BeverageManager beverageManager;
    SocketManager socketManager;

public:
    void selectBeverage(int beverageId, int quantity);
};