#include <unordered_map>
#include "stop.h"
#include "bus.h"
#include "distance_calculator.h"

#ifndef BROWN_BELT_BUS_MANAGER_H
#define BROWN_BELT_BUS_MANAGER_H

class BusManager {
public:
    BusManager();

    void AddStop(Stop &stop);

    void AddBus(Bus &bus);

    std::string GetBusDescription(const std::string &bus_number) const;

private:
    std::unordered_map<std::string_view, Stop> stops;
    std::unordered_map<std::string_view, Bus> buses;
    DistanceCalculator distanceCalculator;
};


#endif //BROWN_BELT_BUS_MANAGER_H
