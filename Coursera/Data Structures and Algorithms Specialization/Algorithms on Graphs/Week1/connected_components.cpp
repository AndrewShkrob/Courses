#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;

void dfs(const vector<vector<int>> &adj, vector<bool> &visited, int x) {
    std::stack<int> to_visit;
    to_visit.push(x);
    while (!to_visit.empty()) {
        x = to_visit.top();
        visited[x] = true;
        to_visit.pop();
        for (int i : adj[x]) {
            if (!visited[i])
                to_visit.push(i);
        }
    }
}

int number_of_components(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    int res = 0;
    for (int i = 0; i < adj.size(); ++i) {
        if (!visited[i]) {
            ++res;
            dfs(adj, visited, i);
        }
    }
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << number_of_components(adj);
}
