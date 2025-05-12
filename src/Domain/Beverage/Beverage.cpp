#include "Beverage.h"

class Beverage{
    private:
        int id;
        string name;
        int stock;

    public:
        bool hasEnoughStock(int quantity){
        return false;
    }

        bool reduceQuantity(int quantity){
        return false;
    }
};