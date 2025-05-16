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
    Beverage();
    Beverage(int id, const string& name, int stock, int price);
    bool hasEnoughStock(int quantity);
    bool reduceQuantity(int quantity);
    int getId();
    int getPrice();
};