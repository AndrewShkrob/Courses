#include <bits/stdc++.h>

using namespace std;

int main() {
    list<int> athletes;
    vector<list<int>::iterator> pos(100000, athletes.end());
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, prev;
        cin >> x >> prev;
        pos[x] = athletes.insert(pos[prev], x);
    }
    for (int &i : athletes) {
        cout << i << " ";
    }
}