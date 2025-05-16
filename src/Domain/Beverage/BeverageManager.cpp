#include "BeverageManager.h"
#include "exception/CustomException.h"

using namespace customException;

bool BeverageManager::hasEnoughStock(int beverageId, int quantity) {
    if(this->beverages.find(beverageId) == beverages.end()){
        throw std::out_of_range("beverageId에 해당하는 음료가 없습니다.");            
        return false;
    }

    Beverage beverage = this->beverages[beverageId];
    return beverage.hasEnoughStock(quantity);
}

bool BeverageManager::reduceQuantity(int beverageId, int quantity) {
    if(this->beverages.find(beverageId) == beverages.end()){
        throw std::out_of_range("beverageId에 해당하는 음료가 없습니다.");            
        return false;
    }

    Beverage beverage = this->beverages[beverageId];
    return beverage.reduceQuantity(quantity);
}

Beverage BeverageManager::getBeverage(int beverageId) {
    if(this->beverages.find(beverageId) == beverages.end()){
        throw std::out_of_range("beverageId에 해당하는 음료가 없습니다.");    
    }

    return this->beverages[beverageId];
}

int BeverageManager::getStock(int beverageId){
        return 0;
}

void BeverageManager::addBeverage(Beverage beverage) {
    beverages.insert({beverage.getId(), beverage});
}
