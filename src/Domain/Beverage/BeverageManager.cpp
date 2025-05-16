#include "BeverageManager.h"
#include "exception/CustomException.h"
using namespace customException;
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
    throw NotFoundException("Beverage not found");
}

int BeverageManager::getStock(int beverageId) {
    return 0;
}

void BeverageManager::addBeverage(const Beverage& beverage) {
    beverages.push_back(beverage);
}