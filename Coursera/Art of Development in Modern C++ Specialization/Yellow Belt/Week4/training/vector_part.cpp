#include <bits/stdc++.h>

using namespace std;

void PrintVectorPart(const vector<int> &numbers) {
    auto it = find_if(numbers.begin(), numbers.end(), [](const int &i) { return i < 0; });
    while (it != numbers.begin()) {
        it--;
        cout << *it << " ";
    }
}