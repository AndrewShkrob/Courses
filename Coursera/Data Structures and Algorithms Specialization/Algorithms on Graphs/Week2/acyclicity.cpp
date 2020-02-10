#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

enum class Color {
    WHITE,
    GREY,
    BLACK
};

int dfs(const vector<vector<int>> &adj, vector<Color> &colors, int vertex) {
    colors[vertex] = Color::GREY;
    for (int i : adj[vertex]) {
        if (colors[i] == Color::GREY)
            return 1;
        if (colors[i] == Color::WHITE)
            if (dfs(adj, colors, i))
                return 1;
    }
    colors[vertex] = Color::BLACK;
    return 0;
}

int acyclic(const vector<vector<int>> &adj) {
    vector<Color> colors(adj.size(), Color::WHITE);
    for (int i = 0; i < adj.size(); ++i) {
        if (colors[i] != Color::BLACK)
            if (dfs(adj, colors, i) == 1)
                return 1;
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
    }
    std::cout << acyclic(adj);
}
