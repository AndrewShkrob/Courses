#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int distance(const vector<vector<pair<int, int>>> &adj, int s, int t) {
    vector<int> dist(adj.size(), std::numeric_limits<int>::max());
    dist[s] = 0;
    priority_queue<pair<int, int>> q;
    q.push({dist[s], s});
    while (!q.empty()) {
        int vertex = q.top().second;
        int cur_distance = -q.top().first;
        q.pop();
        if (cur_distance > dist[vertex])
            continue;
        for (auto node : adj[vertex]) {
            int to = node.first;
            int weight = node.second;
            if (dist[to] > dist[vertex] + weight) {
                dist[to] = dist[vertex] + weight;
                q.push({-dist[to], to});
            }
        }
    }
    return dist[t] == std::numeric_limits<int>::max() ? -1 : dist[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].emplace_back(y - 1, w);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
