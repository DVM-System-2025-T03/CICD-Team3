#pragma once
#include "LocationManager.h"
#include "BeverageManager.h"
#include "SocketManager.h"

class SelectBeverageController {
private:
    LocationManager locationManager;
    BeverageManager beverageManager;
    SocketManager socketManager;

public:
    void selectBeverage(int beverageId, int quantity);
};