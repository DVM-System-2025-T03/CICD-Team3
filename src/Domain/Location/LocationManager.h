#pragma once
#include <list>
#include "Location.h"
#include "../DTO/DVMInfoDTO.h"
#include "../DTO/ResponseStockDTO.h"
using namespace std;

class LocationManager {
private:
    Location location;

public:
    LocationManager() = default;
    DVMInfoDTO calculateNearest(list<ResponseStockDTO> responseList);
    Location getLocation();
};