#pragma once
#include <iostream>

class DVMInfoDTO{
    private:
        double x;
        double y;
    public:
        DVMInfoDTO(double x, double y) : x(x), y(y) {}
        double getX() const { return x; }
        double getY() const { return y; }
};