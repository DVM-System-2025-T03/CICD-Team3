#pragma once
#include <iostream>
#include <string>
using namespace std;

class Beverage {
private:
    int id;
    string name;
    int stock;
    int price;

public:
    bool hasEnoughStock(int quantity);
    bool reduceQuantity(int quantity);
    int getId();
    int getPrice();
};