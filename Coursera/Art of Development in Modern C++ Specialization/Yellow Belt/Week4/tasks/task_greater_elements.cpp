#include <bits/stdc++.h>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
    return vector(upper_bound(elements.begin(), elements.end(), border), elements.end());
}