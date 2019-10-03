#include <bits/stdc++.h>

using namespace std;

template<class T>
class Table {
public:

    Table(const size_t &h, const size_t &w) : h(h), w(w), table(h, vector<T>(w)) {}

    const vector<T> &operator[](const size_t &hh) const {
        return table[hh];
    }

    vector<T> &operator[](const size_t &hh) {
        return table[hh];
    }

    pair<size_t, size_t> Size() const {
        return pair(h, w);
    }

    void Resize(const size_t &hh, const size_t &ww) {
        h = hh;
        w = ww;
        table.resize(h);
        for (auto &v : table)
            v.resize(w);
    }

private:
    size_t h;
    size_t w;
    vector<vector<T>> table;
};