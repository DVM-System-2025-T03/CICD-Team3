#include <map>
#include "Beverage.h"

class BeverageManager{
    private:
        map<int, Beverage> beverages;

    public:
        bool hasEnoughStock(int beverageId, int quantity){
            return false;
        }

        bool reduceQuantity(int beverageId, int quantity){
            return beverages[beverageId].reduceQuantity(quantity);
        }

        Beverage getBeverage(int beverageId){
            return ;
        }

        int getStock(int beverageId){
            return 0;
        }

};