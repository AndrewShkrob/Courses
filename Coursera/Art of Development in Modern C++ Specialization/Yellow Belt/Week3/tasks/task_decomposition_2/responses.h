#include <bits/stdc++.h>

#ifndef C___YELLOW_BELT_RESPONSES_HPP
#define C___YELLOW_BELT_RESPONSES_HPP

using namespace std;

struct BusesForStopResponse {
    vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse {
    bool bus_exists;
    string bus;
    vector<pair<string, vector<string>>> stops_for_bus = {};
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse {
    map<string, vector<string>> all_busses;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);

#endif //C___YELLOW_BELT_RESPONSES_HPP
