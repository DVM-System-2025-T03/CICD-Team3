#pragma once
#include <map>
#include "Beverage.h"
using namespace std;

class BeverageManager {
private:
    map<int, Beverage> beverages;

public:
    BeverageManager() = default;
    bool hasEnoughStock(int beverageId, int quantity);
    bool reduceQuantity(int beverageId, int quantity);
    Beverage getBeverage(int beverageId);
    void addBeverage(Beverage beverage);
    int getStock(int beverageId);
};