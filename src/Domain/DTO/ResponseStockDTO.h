#pragma once
#include <iostream>

class ResponseStockDTO{
    private:
        int id;     // 다른 DVM id
        int beverageId;
        int stock;   
        double x;
        double y;
    public:
        ResponseStockDTO() : id(0), beverageId(0), stock(0), x(0.0), y(0.0) {}
        ResponseStockDTO(int id, int beverageId, int stock, double x, double y) 
            : id(id), beverageId(beverageId), stock(stock), x(x), y(y) {}

        int getId() const { return id; }
        int getBeverageId() const { return beverageId; }
        int getStock() const { return stock; }
        double getX() const { return x; }
        double getY() const { return y; }
};
