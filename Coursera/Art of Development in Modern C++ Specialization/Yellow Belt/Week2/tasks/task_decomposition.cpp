#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type = {};
    string bus = {};
    string stop = {};
    vector<string> stops = {};
};

istream &operator>>(istream &is, Query &q) {
    string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        int stops_count;
        is >> q.bus >> stops_count;
        q.stops.resize(stops_count);
        for (auto &stop : q.stops)
            is >> stop;
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (!r.buses.empty()) {
        for (const auto &bus : r.buses)
            os << bus << " ";
    } else
        os << "No stop";
    return os;
}

struct StopsForBusResponse {
    bool bus_exists;
    string bus;
    vector<pair<string, vector<string>>> stops_for_bus = {};
};

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

struct AllBusesResponse {
    map<string, vector<string>> all_busses;
};

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

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops) {
        for (const auto &stop : stops) {
            buses_for_stops[stop].push_back(bus);
            stops_for_buses[bus].push_back(stop);
        }
    }

    [[nodiscard]] BusesForStopResponse GetBusesForStop(const string &stop) const {
        if (buses_for_stops.find(stop) != buses_for_stops.end())
            return {buses_for_stops.at(stop)};
        else
            return {{}};
    }

    [[nodiscard]] StopsForBusResponse GetStopsForBus(const string &bus) const {
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

    [[nodiscard]] AllBusesResponse GetAllBuses() const {
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

private:
    map<string, vector<string>> buses_for_stops;
    map<string, vector<string>> stops_for_buses;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}