#include <bits/stdc++.h>

using namespace std;

template<class T>
T Sqr(const T &val);

template<class T1, class T2>
pair<T1, T2> Sqr(const pair<T1, T2> &p);

template<class T>
vector<T> Sqr(const vector<T> &v);

template<class K, class V>
map<K, V> Sqr(const map<K, V> &m);

template<class T>
T Sqr(const T &val) {
    return val * val;
}

template<class T1, class T2>
pair<T1, T2> Sqr(const pair<T1, T2> &p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template<class T>
vector<T> Sqr(const vector<T> &v) {
    vector<T> result;
    for (const auto &it : v) {
        result.push_back(Sqr(it));
    }
    return result;
}

template<class K, class V>
map<K, V> Sqr(const map<K, V> &m) {
    map<K, V> result;
    for (const auto &[key, value] : m) {
        result[key] = Sqr(value);
    }
    return result;
}