#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

enum class Color {
    NONE,
    WHITE,
    RED
};

int bipartite(vector<vector<int>> &adj) {
    vector<Color> colors(adj.size(), Color::NONE);
    queue<int> to_visit;
    to_visit.push(0);
    colors[0] = Color::WHITE;
    while (!to_visit.empty()) {
        int vertex = to_visit.front();
        to_visit.pop();
        for (int i : adj[vertex]) {
            if (colors[i] == colors[vertex])
                return 0;
            if (colors[i] == Color::NONE) {
                colors[i] = colors[vertex] == Color::RED ? Color::WHITE : Color::RED;
                to_visit.push(i);
            }
        }
    }
    return 1;
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
    std::cout << bipartite(adj);
}
