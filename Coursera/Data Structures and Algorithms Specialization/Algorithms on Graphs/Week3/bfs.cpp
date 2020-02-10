#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;

int distance(vector<vector<int>> &adj, int s, int t) {
    vector<bool> visited(adj.size(), false);
    queue<pair<int, int>> to_visit;
    to_visit.push({s, 0});
    visited[s] = true;
    while (!to_visit.empty()) {
        auto v_p = to_visit.front();
        to_visit.pop();
        if (v_p.first == t)
            return v_p.second;
        visited[v_p.first] = true;
        for (int i : adj[v_p.first]) {
            if (!visited[i])
                to_visit.push({i, v_p.second + 1});
        }
    }
    return -1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
