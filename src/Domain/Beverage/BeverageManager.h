#pragma once
#include <list>
#include "Beverage.h"
using namespace std;

class BeverageManager {
private:
    list<Beverage> beverages;

public:
    bool hasEnoughStock(int beverageId, int quantity);
    bool reduceQuantity(int beverageId, int quantity);
    Beverage getBeverage(int beverageId);
    void addBeverage(Beverage& beverage);
    int getStock(int beverageId);
};