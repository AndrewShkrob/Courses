#include <bits/stdc++.h>

using namespace std;

pair<int, int> partition3(vector<int> &arr, int left, int right) {
    int pivot = arr[left];
    int left_part = left;
    for (int i = left + 1; i <= right; ++i) {
        if (arr[i] <= pivot) {
            left_part++;
            swap(arr[left_part], arr[i]);
        }
    }
    swap(arr[left], arr[left_part]);
    int right_part = left_part;
    while(arr[right_part] == pivot)
        right_part--;
    for (int i = left; i < right_part; ++i) {
        if (arr[i] == pivot)
            swap(arr[i], arr[right_part--]);
    }
    return {right_part + 1, left_part};
}

void quick_sort(vector<int> &arr, int left, int right) {
    if (left >= right)
        return;
    int k = left + rand() % (right - left + 1);
    swap(arr[left], arr[k]);
    auto m = partition3(arr, left, right);
    quick_sort(arr, left, m.first - 1);
    quick_sort(arr, m.second + 1, right);
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    quick_sort(arr, 0, arr.size() - 1);
    copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    return 0;
} 