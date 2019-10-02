#include "date.h"

Date::Date(int y, int m, int d) : year(y) {
    if (m < 1 || m > 12)
        throw invalid_argument("Month value is invalid: " + to_string(m));
    if (d < 1 || d > 31)
        throw invalid_argument("Day value is invalid: " + to_string(d));
    day = d;
    month = m;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

tuple<int, int, int> Date::MakeTuple() const {
    return tuple(year, month, day);
}

bool Date::operator<(const Date &rhs) const {
    return MakeTuple() < rhs.MakeTuple();
}

bool Date::operator<=(const Date &rhs) const {
    return MakeTuple() <= rhs.MakeTuple();
}

bool Date::operator>(const Date &rhs) const {
    return MakeTuple() > rhs.MakeTuple();
}

bool Date::operator>=(const Date &rhs) const {
    return MakeTuple() >= rhs.MakeTuple();
}

bool Date::operator==(const Date &rhs) const {
    return MakeTuple() == rhs.MakeTuple();
}

bool Date::operator!=(const Date &rhs) const {
    return MakeTuple() != rhs.MakeTuple();
}

void check_and_ignore(istream &stream, const string &str) {
    if (stream.peek() != '-')
        throw invalid_argument("Wrong Date format: " + str);
    stream.ignore(1);
}

istream &operator>>(istream &stream, Date &d) {
    int day;
    int month;
    int year;
    string str_date;
    stream >> str_date;
    stringstream ss(str_date);
    if ((ss.peek() < '0' || ss.peek() > '9') && ss.peek() != '-')
        throw invalid_argument("Wrong date format: " + str_date);
    ss >> year;
    check_and_ignore(ss, str_date);
    if (ss.peek() == -1)
        throw invalid_argument("Wrong date format: " + str_date);
    ss >> month;
    check_and_ignore(ss, str_date);
    if (ss.peek() == -1)
        throw invalid_argument("Wrong date format: " + str_date);
    ss >> day;
    if (!ss.eof())
        throw invalid_argument("Wrong date format: " + str_date);
    d = Date(year, month, day);
    return stream;
}

Date ParseDate(istream &is) {
    Date d;
    is >> d;
    return d;
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
           << setw(2) << setfill('0') << date.GetMonth() << '-'
           << setw(2) << setfill('0') << date.GetDay();
    return stream;
}