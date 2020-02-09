#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;

int reach(const vector<vector<int>> &adj, int x, int y) {
    std::queue<int> to_visit;
    vector<bool> visited(adj.size(), false);
    to_visit.push(x);
    while (!to_visit.empty()) {
        x = to_visit.front();
        visited[x] = true;
        to_visit.pop();
        if (x == y)
            return 1;
        for (int i : adj[x]) {
            if (!visited[i])
                to_visit.push(i);
        }
    }
    return 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
