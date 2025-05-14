#pragma once
#include <iostream>

using namespace std;

class DVMInfoDTO{
    private:
        double x;
        double y;
    public:
        DVMInfoDTO(double x, double y) : x(x), y(y) {}
        double getX() const { return x; }
        double getY() const { return y; }
};