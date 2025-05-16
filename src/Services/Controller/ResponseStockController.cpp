#include "ResponseStockController.h"

ResponseStockDTO ResponseStockController::responseBeverageStock(int beverageId, int quantity) {
    Beverage beverage = this->beverageManager.getBeverage(beverageId);
    Location location = this->locationManager.getLocation();

    return ResponseStockDTO(beverageId, quantity, location.getX(), location.getY());
}