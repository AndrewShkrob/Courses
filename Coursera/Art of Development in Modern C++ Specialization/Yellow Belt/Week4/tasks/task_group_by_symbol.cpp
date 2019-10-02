#include <bits/stdc++.h>

using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix) {
    return make_pair(
            lower_bound(range_begin, range_end, prefix,
                        [](const string &str, const char &prefix) { return str.at(0) < prefix; }),
            upper_bound(range_begin, range_end, prefix,
                        [](const char &prefix, const string &str) { return str.at(0) > prefix; })
    );
}