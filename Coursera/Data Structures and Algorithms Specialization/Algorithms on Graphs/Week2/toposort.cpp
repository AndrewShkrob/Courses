#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<vector<int>> &adj, vector<bool> &used, vector<int> &order, int x) {
    used[x] = true;
    for (int i : adj[x]) {
        if (!used[i])
            dfs(adj, used, order, i);
    }
    order.push_back(x);
}

vector<int> toposort(vector<vector<int>> &adj) {
    vector<bool> used(adj.size(), false);
    vector<int> order;
    for (int i = 0; i < adj.size(); ++i) {
        if (!used[i])
            dfs(adj, used, order, i);
    }
    std::reverse(std::begin(order), std::end(order));
    return order;
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
    vector<int> order = toposort(adj);
    for (int i : order) {
        std::cout << i + 1 << " ";
    }
}
