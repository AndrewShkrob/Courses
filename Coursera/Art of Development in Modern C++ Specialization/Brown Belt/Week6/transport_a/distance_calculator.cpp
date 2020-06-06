#include "distance_calculator.h"
#include <iostream>

using namespace std;

DistanceCalculator::DistanceCalculator(unordered_map<std::string_view, Stop> &stops,
                                       unordered_map<std::string_view, Bus> &buses)
        : stops(stops), buses(buses) {}

double DistanceCalculator::CalculateRouteLengthForBus(const std::string &bus_number) const {
    Bus &bus = buses[bus_number];
    const auto &stop_names = bus.GetStopNames();
    double distance = 0;
    for (auto start = begin(stop_names); start != prev(end(stop_names)); ++start) {
        distance += Calculate(stops.at(*start).coords, stops.at(*next(start)).coords);
    }
    return distance;
}

double DistanceCalculator::Calculate(Coords point1, Coords point2) const {
    double dLat = DegToRad(point2.latitude - point1.latitude);
    double dLon = DegToRad(point2.longitude - point1.longitude);
    double a = pow(sin(dLat / 2), 2) +
               cos(DegToRad(point1.latitude)) * cos(DegToRad(point2.latitude)) *
               pow(sin(dLon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return abs(EARTH_RADIUS * c) * 1000;
}

double DistanceCalculator::DegToRad(double degrees) {
    return degrees * (PI / 180);
}