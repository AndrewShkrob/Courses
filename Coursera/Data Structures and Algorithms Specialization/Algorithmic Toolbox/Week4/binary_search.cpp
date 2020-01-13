#include <bits/stdc++.h>

using namespace std;

int binary_search(const vector<int> &a, int x, int left, int right) {
    int mid = left + (right - left) / 2;
    if (left > right)
        return -1;
    if (a[mid] == x)
        return mid;
    else if (a[mid] > x)
        return binary_search(a, x, left, mid - 1);
    else
        return binary_search(a, x, mid + 1, right);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int m;
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cout << binary_search(a, b[i], 0, a.size() - 1) << ' ';
    }
} 