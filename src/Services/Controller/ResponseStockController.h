#pragma once
#include "../../Domain/Location/LocationManager.h"
#include "../../Domain/Beverage/BeverageManager.h"
#include "../../Domain/DTO/ResponseStockDTO.h"

class ResponseStockController {
private:
    LocationManager locationManager;
    BeverageManager beverageManager;

public:
    ResponseStockDTO responseBeverageStock(int beverageId, int quantity);
};