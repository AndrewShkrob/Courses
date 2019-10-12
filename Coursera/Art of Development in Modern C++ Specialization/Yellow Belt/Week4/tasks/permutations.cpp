#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    generate(nums.begin(), nums.end(), [&n]() { return n--; });
    do {
        for (const auto &it : nums) {
            cout << it << " ";
        }
        cout << endl;
    } while (prev_permutation(nums.begin(), nums.end()));
}