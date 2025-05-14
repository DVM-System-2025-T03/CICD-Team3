#include <list>
#include "Beverage.h"

class BeverageManager{
    private:
        list<Beverage> beverages;

    public:
        bool hasEnoughStock(int beverageId, int quantity){
            for (Beverage beverage : beverages) {
                if (beverage.getId() == beverageId) {
                    return beverage.hasEnoughStock(quantity);
                }
            }

            throw std::out_of_range("beverageId에 해당하는 음료가 없습니다.");            
        }

        bool reduceQuantity(int beverageId, int quantity){
        return false;
    }

        Beverage getBeverage(int beverageId){
        return ;
    }

        int getStock(int beverageId){
        return 0;
    }

};