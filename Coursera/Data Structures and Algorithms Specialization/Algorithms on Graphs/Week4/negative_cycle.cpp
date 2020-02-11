#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int negative_cycle(const vector<vector<pair<int, int>>> &adj) {
    vector<int> dist(adj.size(), 1000000);
    dist[0] = 0;
    for (int n = 0; n < adj.size(); ++n) {
        bool relaxed = false;
        for (int i = 0; i < adj.size(); ++i) {
            int from = i;
            for (const auto &node : adj[from]) {
                int to = node.first;
                int weight = node.second;
                if (dist[to] > dist[from] + weight) {
                    dist[to] = dist[from] + weight;
                    relaxed = true;
                }
            }
        }
        if (!relaxed)
            return 0;
    }
    return 1;
}

int main() {
    vector<vector<int>> v;
    int n, m;
    std::cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].emplace_back(y - 1, w);
    }
    std::cout << negative_cycle(adj);
}
