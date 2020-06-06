#include "bus.h"
#include "bus_builder.h"

using namespace std;

Bus::Bus(string &number, string &stops_config, vector<std::string_view> &stop_names)
        : number(move(number)),
          stops_config(move(stops_config)),
          stop_names(move(stop_names)) {}

const string &Bus::GetNumber() const {
    return number;
}

size_t Bus::GetStopsCount() const {
    return stop_names.size();
}

size_t Bus::GetUniqueStopsCount() const {
    unordered_map<string_view, size_t> stops;
    for (const auto &stop_name : stop_names) {
        stops[stop_name]++;
    }
    return stops.size();
}

const std::vector<std::string_view> &Bus::GetStopNames() const {
    return stop_names;
}

istream &operator>>(istream &is, Bus &bus) {
    string number;
    string stops;
    while (is.peek() == ' ')
        is.ignore();
    getline(is, number, ':');
    getline(is, stops);
    bus = BusBuilder().SetBusNumber(number).ConfigureStops(stops).Build();
    return is;
}