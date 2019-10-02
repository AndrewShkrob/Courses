#ifndef C___YELLOW_BELT_DATABASE_H
#define C___YELLOW_BELT_DATABASE_H

#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include "date.h"

using std::string;
using std::ostream;
using std::vector;
using std::map;
using std::set;
using std::list;
using std::pair;
using std::endl;

class Database {
public:
    Database() = default;

    void Add(const Date &date, const string &event);

    void Print(ostream &os) const;

    string Last(const Date &date) const;

    vector<pair<Date, string>> FindIf(const std::function<bool(Date, string)> &predicate) const;

    int RemoveIf(const std::function<bool(Date, string)> &predicate);

private:
    map<Date, set<string>> sorted_data;
    map<Date, vector<string>> data;
};

ostream &operator<<(ostream &os, const pair<Date, string> &event);

#endif //C___YELLOW_BELT_DATABASE_H
