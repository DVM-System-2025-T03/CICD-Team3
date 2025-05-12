#pragma once
#include "LocationManager.h"
#include "BeverageManager.h"
#include "ResponseStockDTO.h"

class ResponseStockController {
private:
    LocationManager locationManager;
    BeverageManager beverageManager;

public:
    ResponseStockDTO responseBeverageStock(int beverageId, int quantity);
};