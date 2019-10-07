#include "airline_ticket.h"
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

bool operator==(const Date &lhs, const Date &rhs) {
    return tuple(lhs.year, lhs.month, lhs.day) == tuple(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date &lhs, const Date &rhs) {
    return tuple(lhs.year, lhs.month, lhs.day) < tuple(rhs.year, rhs.month, rhs.day);
}

ostream &operator<<(ostream &os, Date &d) {
    return os;
}

bool operator==(const Time &lhs, const Time &rhs) {
    return tuple(lhs.hours, lhs.minutes) == tuple(rhs.hours, rhs.minutes);
}

bool operator<(const Time &lhs, const Time &rhs) {
    return tuple(lhs.hours, lhs.minutes) < tuple(rhs.hours, rhs.minutes);
}

ostream &operator<<(ostream &os, Time &t) {
    return os;
}

#define SORT_BY(field) [](const AirlineTicket &lhs, const AirlineTicket &rhs) { return lhs.field < rhs.field; }