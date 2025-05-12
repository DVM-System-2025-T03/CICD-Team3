#include <list>
#include "Beverage.h"

class BeverageManager{
    private:
        list<Beverage> beverages;

    public:
        bool hasEnoughStock(int beverageId, int quantity){
        return false;
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