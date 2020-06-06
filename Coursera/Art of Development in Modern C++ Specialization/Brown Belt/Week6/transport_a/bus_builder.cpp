#include "bus_builder.h"

using namespace std;

BusBuilder &BusBuilder::SetBusNumber(string &number) {
    bus_number = move(number);
    return *this;
}

BusBuilder &BusBuilder::ConfigureStops(string &stops_config) {
    this->stops_config = move(stops_config);
    this->route_type = GetRouteType(this->stops_config);
    char separator = static_cast<char>(route_type);
    for (auto stop_name : SplitBy(this->stops_config, separator)) {
        stop_names.emplace_back(Strip(stop_name));
    }
    if (this->route_type == RouteType::ROUND) {
        std::list<std::string_view> second_part(begin(stop_names), prev(end(stop_names)));
        reverse(begin(second_part), end(second_part));
        move(begin(second_part), end(second_part), back_inserter(stop_names));
    }
    return *this;
}

Bus BusBuilder::Build() {
    return Bus(bus_number, stops_config, stop_names);
}

BusBuilder::RouteType BusBuilder::GetRouteType(const std::string &stops_config) {
    for (char i : stops_config) {
        if (i == '>')
            return RouteType::RING;
        else if (i == '-')
            return RouteType::ROUND;
    }
    return RouteType::NONE;
}