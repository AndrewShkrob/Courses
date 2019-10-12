#include <bits/stdc++.h>

using namespace std;

template<class K, class V>
V &GetRefStrict(map<K, V> &m, const K &key) {
    if (m.find(key) == m.end())
        throw runtime_error("");
    return m[key];
}