#include "BeverageManager.h"
#include "exception/CustomException.h"

using namespace customException;

bool BeverageManager::hasEnoughStock(int beverageId, int quantity) {
    for (Beverage beverage : beverages) {
        if (beverage.getId() == beverageId) {
            return beverage.hasEnoughStock(quantity);
        }
    }

    throw std::out_of_range("beverageId에 해당하는 음료가 없습니다.");            
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

        throw NotFoundException("Beverage not found");
    }
}

int BeverageManager::getStock(int beverageId){
        return 0;
}

void BeverageManager::addBeverage(const Beverage& beverage) {
    beverages.push_back(beverage);
}
