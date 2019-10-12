#include <bits/stdc++.h>

#ifndef C___YELLOW_BELT_QUERY_H
#define C___YELLOW_BELT_QUERY_H

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
    vector <string> stops = {};
};

istream &operator>>(istream &is, Query &q);

#endif //C___YELLOW_BELT_QUERY_H
