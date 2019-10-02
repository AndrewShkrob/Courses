#include <bits/stdc++.h>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border) {
    const auto &left = numbers.lower_bound(border);
    if (left == numbers.begin())
        return left;
    if (left == numbers.end())
        return prev(left);
    return (border - *prev(left) <= *left - border) ? prev(left) : left;
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}