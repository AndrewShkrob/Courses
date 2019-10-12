#include "responses.h"

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (!r.buses.empty()) {
        for (const auto &bus : r.buses)
            os << bus << " ";
    } else
        os << "No stop";
    return os;
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (r.bus_exists) {
        for (const auto &[stop, buses_list] : r.stops_for_bus) {
            os << "Stop " << stop << ": ";
            if (buses_list.empty()) {
                os << "no interchange" << endl;
                continue;
            }
            for (const auto &bus : buses_list) {
                if (bus == r.bus)
                    continue;
                os << bus << " ";
            }
            os << endl;
        }
    } else {
        os << "No bus";
    }
    return os;
}

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (r.all_busses.empty()) {
        os << "No buses";
    } else {
        for (const auto &[bus, stops] : r.all_busses) {
            os << "Bus " << bus << ": ";
            for (const auto &stop : stops) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}