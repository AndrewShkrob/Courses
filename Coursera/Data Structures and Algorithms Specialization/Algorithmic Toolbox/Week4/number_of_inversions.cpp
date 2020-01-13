#include <bits/stdc++.h>

using namespace std;

int merge(vector<int> &arr, int left, int mid, int right) {
    int inversions = 0;
    vector<int> left_part(mid - left + 1);
    vector<int> right_part(right - mid);
    for (int i = 0; i < left_part.size(); i++)
        left_part[i] = arr[left + i];
    for (int i = 0; i < right_part.size(); i++)
        right_part[i] = arr[mid + 1 + i];
    int i = 0;
    int j = 0;
    int k = left;
    while (i < left_part.size() && j < right_part.size()) {
        if (left_part[i] <= right_part[j])
            arr[k++] = left_part[i++];
        else {
            arr[k++] = right_part[j++];
            inversions += left_part.size() - i;
        }
    }
    while (i < left_part.size())
        arr[k++] = left_part[i++];
    while (j < right_part.size())
        arr[k++] = right_part[j++];
    return inversions;
}

int merge_sort(vector<int> &arr, int left, int right, int inversions = 0) {
    int mid = (right + left) / 2;
    if (left < right) {
        inversions += merge_sort(arr, left, mid);
        inversions += merge_sort(arr, mid + 1, right);
        inversions += merge(arr, left, mid, right);
    }
    return inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        std::cin >> i;
    }
    cout << merge_sort(a, 0, a.size() - 1);
    return 0;
}