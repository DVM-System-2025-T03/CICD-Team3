
#pragma once
#include <iostream>

using namespace std;

class Location{
    private:
        double x;
        double y;

    public:
        int getX(){
            return this->x;
        }

        int getY(){
            return this->y;
        }
};