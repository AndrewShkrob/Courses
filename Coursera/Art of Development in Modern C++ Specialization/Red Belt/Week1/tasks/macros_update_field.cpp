#include "airline_ticket.h"
#include <bits/stdc++.h>

using namespace std;

bool operator < (const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator < (const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator == (const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << d.year << '-' << d.month << '-' << d.day;
}

ostream& operator<<(ostream& os, const Time& t) {
    return os << t.hours << ':' << t.minutes;
}

istream& operator>>(istream& is, Date& d) {
    is >> d.year;
    is.ignore(1);
    is >> d.month;
    is.ignore(1);
    is >> d.day;
    return is;
}

istream& operator>>(istream& is, Time& t) {
    is >> t.hours;
    is.ignore(1);
    is >> t.minutes;
    return is;
}

#define UPDATE_FIELD(ticket, field, values) { \
    auto it = values.find(#field);            \
    if (it != values.end()) {                 \
        istringstream is(it->second);         \
        is >> ticket.field;                   \
    }                                         \
}
