#include "BeverageManager.h"

bool BeverageManager::hasEnoughStock(int beverageId, int quantity) {
    return false;
}

bool BeverageManager::reduceQuantity(int beverageId, int quantity) {
    return false;
}

Beverage BeverageManager::getBeverage(int beverageId) {
    for(list<Beverage>::iterator bevgerage = beverages.begin(); bevgerage != beverages.end(); bevgerage++){
        if(bevgerage->getId() == beverageId){
            return *bevgerage;
        }
    }
    return Beverage();
}

int BeverageManager::getStock(int beverageId) {
    return 0;
}