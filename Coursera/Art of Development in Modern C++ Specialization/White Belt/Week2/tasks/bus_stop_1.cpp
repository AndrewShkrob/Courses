#include <bits/stdc++.h>

using namespace std;

map<string, vector<string>> buses_for_stops;
map<string, vector<string>> stops_for_buses;

void new_bus() {
    string bus;
    int stop_count;
    cin >> bus >> stop_count;
    while (stop_count--) {
        string stop_name;
        cin >> stop_name;
        buses_for_stops[stop_name].push_back(bus);
        stops_for_buses[bus].push_back(stop_name);
    }
}

void buses_for_stop() {
    string stop_name;
    cin >> stop_name;
    if (buses_for_stops.find(stop_name) != buses_for_stops.end()) {
        for (const auto &bus : buses_for_stops[stop_name])
            cout << bus << " ";
        cout << endl;
    } else
        cout << "No stop" << endl;
}

void stops_for_bus() {
    string bus;
    cin >> bus;
    if (stops_for_buses.find(bus) == stops_for_buses.end()) {
        cout << "No bus" << endl;
        return;
    }
    for (const auto &stop : stops_for_buses[bus]) {
        cout << "Stop " << stop << ": ";
        if (buses_for_stops[stop].size() < 2) {
            cout << "no interchange" << endl;
            continue;
        }
        for (const auto &b : buses_for_stops[stop]) {
            if (b == bus)
                continue;
            cout << b << " ";
        }
        cout << endl;
    }
}

void all_buses() {
    if (stops_for_buses.empty()) {
        cout << "No buses" << endl;
        return;
    }
    for (const auto &[bus, stops] : stops_for_buses) {
        cout << "Bus " << bus << ": ";
        for (const auto &stop : stops) {
            cout << stop << " ";
        }
        cout << endl;
    }
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        string str;
        cin >> str;
        if (str == "NEW_BUS")
            new_bus();
        else if (str == "BUSES_FOR_STOP")
            buses_for_stop();
        else if (str == "STOPS_FOR_BUS")
            stops_for_bus();
        else if (str == "ALL_BUSES")
            all_buses();
    }
}