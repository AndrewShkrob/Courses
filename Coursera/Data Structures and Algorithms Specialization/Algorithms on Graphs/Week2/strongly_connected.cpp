#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs(const vector<vector<int>> &adj, vector<bool> &used, vector<int> &out_vertex_order, int vertex) {
    used[vertex] = true;
    for (int i : adj[vertex]) {
        if (!used[i])
            dfs(adj, used, out_vertex_order, i);
    }
    out_vertex_order.push_back(vertex);
}

void dfs(const vector<vector<int>> &adj, vector<bool> &used, int vertex) {
    used[vertex] = true;
    for (int i : adj[vertex]) {
        if (!used[i])
            dfs(adj, used, i);
    }
}

vector<int> get_vertex_out_order(const vector<vector<int>> &adj) {
    vector<bool> used(adj.size(), false);
    vector<int> out_vertex_order;
    for (int i = 0; i < adj.size(); ++i) {
        if (!used[i])
            dfs(adj, used, out_vertex_order, i);
    }
    return out_vertex_order;
}

int number_of_strongly_connected_components(const vector<vector<int>> &adj, const vector<vector<int>> &adj_inv) {
    int result = 0;
    vector<int> out_vertex_order = get_vertex_out_order(adj);
    std::reverse(std::begin(out_vertex_order), std::end(out_vertex_order));
    vector<bool> used(adj.size(), false);
    for (int i : out_vertex_order) {
        if (!used[i]) {
            dfs(adj_inv, used, i);
            ++result;
        }
    }
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> adj_inv(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj_inv[y - 1].push_back(x - 1);
    }
    std::cout << number_of_strongly_connected_components(adj, adj_inv);
}
