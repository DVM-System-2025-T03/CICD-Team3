
#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Location{
    private:
        double x;
        double y;

    public:
        double distanceTo(double x, double y) const {
            double dx = this->x - x;
            double dy = this->y - y;
            return std::sqrt(dx * dx + dy * dy);
        }
};