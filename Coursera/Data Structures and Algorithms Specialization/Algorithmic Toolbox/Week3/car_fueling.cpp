#include <bits/stdc++.h>

using namespace std;

int compute_min_refills(int tank, vector<int> &stops) {
    int num_refills = 0;
    int current_refill = 0;
    while (current_refill < stops.size()) {
        int last_refill = current_refill;
        while (current_refill < stops.size() && stops[current_refill + 1] - stops[last_refill] <= tank)
            ++current_refill;
        if (current_refill == last_refill)
            return -1;
        if (current_refill < stops.size())
            ++num_refills;
    }
    return num_refills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n + 1);
    stops[0] = 0;
    for (size_t i = 1; i <= n; ++i)
        cin >> stops.at(i);
    stops.push_back(d);

    cout << compute_min_refills(m, stops) << "\n";

    return 0;
}