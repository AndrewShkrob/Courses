#ifndef C___YELLOW_BELT_BUS_MANAGER_H
#define C___YELLOW_BELT_BUS_MANAGER_H

#include "responses.h"

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops);

    [[nodiscard]] BusesForStopResponse GetBusesForStop(const string &stop) const;

    [[nodiscard]] StopsForBusResponse GetStopsForBus(const string &bus) const;

    [[nodiscard]] AllBusesResponse GetAllBuses() const;

private:
    map<string, vector<string>> buses_for_stops;
    map<string, vector<string>> stops_for_buses;
};

#endif //C___YELLOW_BELT_BUS_MANAGER_H
