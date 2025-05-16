#include "Beverage.h"

Beverage::Beverage():id(0), name("name"), stock(0), price(0){};

Beverage::Beverage(int id, const string& name, int stock, int price)
    :id(id), name(name), stock(stock), price(price){};

bool Beverage::hasEnoughStock(int quantity){
    return false;
}

bool Beverage::reduceQuantity(int quantity){
    return false;
}

int Beverage::getId(){
    return id;
}

int Beverage::getPrice(){
    return price;
}