#include "Beverage.h"

bool Beverage::hasEnoughStock(int quantity){
    return false;
}

bool Beverage::reduceQuantity(int quantity){
    if (quantity < 0) {
        return false;
    }

    if (stock < quantity) {
        return false;
    }

    stock -= quantity;
    return true;
}

int Beverage::getId(){
    return id;
}

int Beverage::getPrice(){
    return price;
}