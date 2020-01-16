#include <bits/stdc++.h>

using namespace std;

vector<int> get_max_in_range(const vector<int> &numbers, int range) {
    vector<int> ans;
    deque<int> dq;
    for (int i = 0; i < numbers.size(); i++) {
        if (!dq.empty() && dq.front() == i - range)
            dq.pop_front();
        while (!dq.empty() && numbers[dq.back()] <= numbers[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= range - 1)
            ans.push_back(numbers[dq.front()]);
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (auto &i : numbers)
        cin >> i;
    int range;
    cin >> range;
    for (int max : get_max_in_range(numbers, range)) {
        cout << max << " ";
    }
}