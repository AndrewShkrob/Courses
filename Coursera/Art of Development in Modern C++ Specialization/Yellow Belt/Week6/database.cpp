#include <iostream>
#include "database.h"

void Database::Add(const Date &date, const string &event) {
    if (sorted_data.count(date) == 0 || sorted_data[date].count(event) == 0) {
        sorted_data[date].insert((event));
        data[date].push_back(event);
    }
}

void Database::Print(ostream &os) const {
    for (const auto &[date, list] : data) {
        for (const auto &event : list) {
            os << pair(date, event) << endl;
        }
    }
}

string Database::Last(const Date &date) const {
    if (date < data.begin()->first || data.empty()) {
        throw invalid_argument("");
    };
    auto it = --(data.upper_bound(date));
    stringstream ss;
    ss << it->first << " " << it->second.back();
    return ss.str();
}

vector<pair<Date, string>> Database::FindIf(const std::function<bool(Date, string)> &predicate) const {
    vector<pair<Date, string>> events;
    for (const auto &[date, vector] : data) {
        for (const auto &event : vector) {
            if (predicate(date, event))
                events.emplace_back(date, event);
        }
    }
    return events;
}

int Database::RemoveIf(const std::function<bool(Date, string)> &predicate) {
    int count = 0;
    auto it_storage = data.begin();
    while (it_storage != data.end()) {
        auto it_events = stable_partition(it_storage->second.begin(), it_storage->second.end(),
                                          [&](const string &str) { return !predicate(it_storage->first, str); });
        if (it_events != it_storage->second.end()) {
            count += distance(it_events, it_storage->second.end());
            it_storage->second.erase(it_events, it_storage->second.end());
            sorted_data[it_storage->first].clear();
            sorted_data[it_storage->first].insert(it_storage->second.begin(), it_storage->second.end());
        }
        if (it_storage->second.empty()) {
            sorted_data.erase(it_storage->first);
            it_storage = data.erase(it_storage);
        } else {
            ++it_storage;
        }
    }
    return count;
}

ostream &operator<<(ostream &os, const pair<Date, string> &event) {
    return os << event.first << " " << event.second;
}