#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
    for (const auto &stop : stops) {
        buses_for_stops[stop].push_back(bus);
        stops_for_buses[bus].push_back(stop);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
    if (buses_for_stops.find(stop) != buses_for_stops.end())
        return {buses_for_stops.at(stop)};
    else
        return {{}};
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
    if (stops_for_buses.find(bus) == stops_for_buses.end())
        return {false, bus, {}};
    vector<pair<string, vector<string>>> stops_for_bus;
    for (const auto &stop : stops_for_buses.at(bus)) {
        stops_for_bus.emplace_back(stop, vector<string>());
        for (const auto &b : buses_for_stops.at(stop)) {
            if (b == bus)
                continue;
            stops_for_bus.back().second.push_back(b);
        }
    }
    return {true, bus, stops_for_bus};
}

AllBusesResponse BusManager::GetAllBuses() const {
    if (stops_for_buses.empty()) {
        return {};
    }
    map<string, vector<string>> result;
    for (const auto &[bus, stops] : stops_for_buses) {
        for (const auto &stop : stops) {
            result[bus].push_back(stop);
        }
    }
    return {result};
}