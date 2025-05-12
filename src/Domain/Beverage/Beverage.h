#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <iostream>
#include <string>
using namespace std;

class Beverage {
private:
    int id;
    string name;
    int stock;

public:
    bool hasEnoughStock(int quantity);
    bool reduceQuantity(int quantity);
};

#endif