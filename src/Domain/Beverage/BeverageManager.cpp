#include "BeverageManager.h"

Beverage::Beverage() : id(0), name(""), stock(0), price(0) {}

Beverage::Beverage(int id, string& name, int stock, int price)
        : id(id), name(name), stock(stock), price(price) {}

bool BeverageManager::hasEnoughStock(int beverageId, int quantity) {
    return false;
}

bool BeverageManager::reduceQuantity(int beverageId, int quantity) {
    for (auto& beverage : beverages) {
        if (beverage.getId() == beverageId) {
            return beverage.reduceQuantity(quantity);
        }
    }

    return false;       // 해당 ID의 음료가 없을 경우
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

void BeverageManager::addBeverage(Beverage& beverage) {
    beverages.push_back(beverage);
}