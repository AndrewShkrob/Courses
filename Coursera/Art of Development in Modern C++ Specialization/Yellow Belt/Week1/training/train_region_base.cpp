#include <bits/stdc++.h>

using namespace std;

bool operator<(const Region &lhs, const Region &rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
    if (regions.empty())
        return 0;
    map<Region, int> counts;

    for (const auto &region : regions)
        counts[region]++;
    int repetitions_count = 0;
    for (const auto &[k, v] : counts)
        repetitions_count = max(repetitions_count, v);
    return repetitions_count;
}