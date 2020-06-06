#include <iomanip>
#include "bus_manager.h"

using namespace std;

BusManager::BusManager() : distanceCalculator({stops, buses}) {}

void BusManager::AddStop(Stop &stop) {
    stops.insert({"", move(stop)});
    auto node = stops.extract("");
    node.key() = node.mapped().name;
    stops.insert(move(node));
}

void BusManager::AddBus(Bus &bus) {
    buses.insert({"", move(bus)});
    auto node = buses.extract("");
    node.key() = node.mapped().GetNumber();
    buses.insert(move(node));
}

string BusManager::GetBusDescription(const string &bus_number) const {
    if (buses.find(bus_number) == buses.end())
        return "Bus " + bus_number + ": not found";
    const Bus &bus = buses.at(bus_number);
    size_t stops_count = bus.GetStopsCount();
    size_t unique_stops_count = bus.GetUniqueStopsCount();
    double route_length = distanceCalculator.CalculateRouteLengthForBus(bus_number);
    ostringstream os;
    os << setprecision(6);
    os << "Bus " << bus_number << ": " << stops_count << " stops on route, " << unique_stops_count
       << " unique stops, " << route_length << " route length";
    return os.str();
}