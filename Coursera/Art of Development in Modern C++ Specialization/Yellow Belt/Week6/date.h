#ifndef C___YELLOW_BELT_DATE_H
#define C___YELLOW_BELT_DATE_H

#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include <tuple>

using std::string;
using std::to_string;
using std::invalid_argument;
using std::istream;
using std::ostream;
using std::stringstream;
using std::setw;
using std::setfill;
using std::tuple;

class Date {
public:
    Date(int y = 1, int m = 1, int d = 1);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

    bool operator<(const Date &rhs) const;

    bool operator<=(const Date &rhs) const;

    bool operator>(const Date &rhs) const;

    bool operator>=(const Date &rhs) const;

    bool operator==(const Date &rhs) const;

    bool operator!=(const Date &rhs) const;

private:
    tuple<int, int, int> MakeTuple() const;

    int year;
    int month;
    int day;
};

void check_and_ignore(istream &stream, const string &str);

istream &operator>>(istream &stream, Date &d);

ostream &operator<<(ostream &stream, const Date &date);

Date ParseDate(istream &is);

#endif
