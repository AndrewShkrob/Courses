#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <numeric>

using std::vector;
using std::pair;

struct DisjointSets {
    vector<int> sets;

    explicit DisjointSets(int size) : sets(size) {
        std::iota(std::begin(sets), std::end(sets), 0);
    }

    int getParent(int vertex) {
        if (sets[vertex] != vertex) {
            sets[vertex] = getParent(sets[vertex]);
        }
        return sets[vertex];
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination == realSource)
            return;
        sets[realSource] = realDestination;
    }
};

struct Edge {
    int from;
    int to;
    double weight;

    bool operator<(const Edge &edge) const {
        return weight < edge.weight;
    }
};

double clustering(const vector<pair<int, int>> &coords, int k) {
    vector<Edge> edges;
    // generate edges
    for (int i = 0; i < coords.size(); ++i) {
        for (int j = i + 1; j < coords.size(); ++j) {
            double weight = sqrt(
                    pow(coords[i].first - coords[j].first, 2) + pow(coords[i].second - coords[j].second, 2));
            edges.push_back({i, j, weight});
        }
    }
    std::sort(std::begin(edges), std::end(edges));
    vector<Edge> mst;
    DisjointSets ds(coords.size());
    for (const auto &edge : edges) {
        if (ds.getParent(edge.from) != ds.getParent(edge.to)) {
            ds.merge(edge.from, edge.to);
            mst.emplace_back(edge);
        }
    }
    std::sort(std::begin(mst), std::end(mst));
    return std::min_element(std::end(mst) - k + 1, std::end(mst))->weight;
}

int main() {
    size_t n;
    int k;
    std::cin >> n;
    vector<pair<int, int>> coords(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> coords[i].first >> coords[i].second;
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(coords, k) << std::endl;
}
