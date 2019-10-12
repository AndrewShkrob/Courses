#include <bits/stdc++.h>

using namespace std;

int main() {
    map<vector<string>, int> stops;
    int q;
    cin >> q;
    while(q--) {
        int n;
        cin >> n;
        vector<string> _stops;
        while(n--) {
            string stop;
            cin >> stop;
            _stops.push_back(stop);
        }
        int size = stops.size() + 1;
        if (stops.find(_stops) != stops.end()) {
            cout << "Already exists for " << stops[_stops] << endl;
            continue;
        } else {
            cout << "New bus " << size << endl;
            stops[_stops] = size;
        }
    }
}