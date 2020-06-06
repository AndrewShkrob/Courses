#include <unordered_map>
#include <string>
#include <string_view>
#include <cmath>
#include "stop.h"
#include "bus.h"

#ifndef BROWN_BELT_DISTANCE_CALCULATOR_H
#define BROWN_BELT_DISTANCE_CALCULATOR_H

class DistanceCalculator {
public:
    DistanceCalculator(std::unordered_map<std::string_view, Stop> &stops,
                       std::unordered_map<std::string_view, Bus> &buses);

    double CalculateRouteLengthForBus(const std::string &bus_number) const;

    double Calculate(Coords point1, Coords point2) const;

private:
    static double DegToRad(double degrees);

private:
    constexpr static const double PI = 3.1415926535;
    constexpr static const int EARTH_RADIUS = 6371;

    std::unordered_map<std::string_view, Stop> &stops;
    std::unordered_map<std::string_view, Bus> &buses;
};

#endif //BROWN_BELT_DISTANCE_CALCULATOR_H
