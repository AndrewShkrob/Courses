#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void bfs_to_mark_nodes_reachable(const vector<vector<pair<int, int>>> &adj, vector<bool> &reachable, int s) {
    vector<bool> used(adj.size(), false);
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (used[v])
            continue;
        used[v] = true;
        reachable[v] = true;
        for (const auto &node : adj[v]) {
            int to = node.first;
            if (!used[to])
                q.push(to);
        }
    }
}

void bfs_to_mark_nodes_shortest(const vector<vector<pair<int, int>>> &adj, vector<bool> &shortest, queue<int> &q) {
    vector<bool> used(adj.size(), false);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (used[v])
            continue;
        used[v] = true;
        shortest[v] = false;
        for (const auto &node : adj[v]) {
            int to = node.first;
            if (!used[to])
                q.push(to);
        }
    }
}

void shortest_paths(const vector<vector<pair<int, int>>> &adj, int s, vector<long long> &dist,
                    vector<bool> &reachable, vector<bool> &shortest) {
    bfs_to_mark_nodes_reachable(adj, reachable, s);
    // q - relaxed vertices on last iteration
    queue<int> q;
    dist[s] = 0;
    for (int n = 0; n < adj.size(); ++n) {
        for (int i = 0; i < adj.size(); ++i) {
            int from = i;
            for (const auto &node : adj[from]) {
                int to = node.first;
                int weight = node.second;
                if (dist[to] > dist[from] + weight && dist[from] != std::numeric_limits<long long>::max()) {
                    dist[to] = dist[from] + weight;
                    if (n + 1 == adj.size())
                        q.push(to);
                }
            }
        }
    }
    bfs_to_mark_nodes_shortest(adj, shortest, q);
}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].emplace_back(y - 1, w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<bool> reachable(n, false);
    vector<bool> shortest(n, true);
    shortest_paths(adj, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
