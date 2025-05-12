#pragma once
#include <list>
#include "Location.h"
#include "DVMInfoDTO.h"
#include "ResponseStockDTO.h"
using namespace std;

class LocationManager {
private:
    Location location;

public:
    DVMInfoDTO calculateNearest(list<ResponseStockDTO> responseList);
    Location getLocation();
};