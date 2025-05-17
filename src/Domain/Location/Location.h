
#pragma once
#include <iostream>
#include <cmath>

class Location{
    private:
        double x;
        double y;

    public:
        Location() = default;
        int getX(){
            return this->x;
        }

        int getY(){
            return this->y;
        }

        double distanceTo(double otherX, double otherY) const {
            double dx = this->x - otherX;
            double dy = this->y - otherY;
            return std::sqrt(dx * dx + dy * dy);
        }
};