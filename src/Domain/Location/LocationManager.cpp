#include "LocationManager.h"
#include <limits>

DVMInfoDTO LocationManager::calculateNearest(list<ResponseStockDTO> responseList) {
    if (responseList.empty()) {
        throw std::invalid_argument("responseList is empty");
    }

    double minDist = std::numeric_limits<double>::max();
    
    DVMInfoDTO nearestDVM(0, 0); 
    for (const auto& response : responseList) {
        double dist = location.distanceTo(response.getX(), response.getY());
        if (dist < minDist) {
            minDist = dist;
            nearestDVM = DVMInfoDTO(response.getX(), response.getY());
        }
    }

    return nearestDVM;
}

Location LocationManager::getLocation() {
    return Location();
}