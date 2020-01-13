#include <bits/stdc++.h>

using namespace std;

int get_majority_element(const vector<int> &arr, int left, int right) {
    if (left == right)
        return -1;
    if (left + 1 == right)
        return arr[left];

    int mid = left + (right - left) / 2;
    int left_majority = get_majority_element(arr, left, mid);
    int right_majority = get_majority_element(arr, mid, right);

    int left_cnt = 0;
    int right_cnt = 0;
    for (int i = left; i < right; ++i) {
        if (arr[i] == left_majority)
            left_cnt++;
        else if (arr[i] == right_majority)
            right_cnt++;
    }
    if (left_cnt * 2 > (right - left))
        return left_majority;
    if (right_cnt * 2 > (right - left))
        return right_majority;
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }
    cout << (get_majority_element(a, 0, n) != -1);
    return 0;
} 