#include <bits/stdc++.h>

using namespace std;

vector<int> backtrack(const vector<int> &num_operations, int number) {
    vector<int> path;
    path.push_back(number);
    while (number != 1) {
        if (number % 3 == 0 && num_operations[number] - 1 == num_operations[number / 3]) {
            path.push_back(number / 3);
            number /= 3;
        } else if (number % 2 == 0 && num_operations[number] - 1 == num_operations[number / 2]) {
            path.push_back(number / 2);
            number /= 2;
        } else {
            path.push_back(number - 1);
            --number;
        }
    }
    reverse(begin(path), end(path));
    return path;
}

vector<int> get_path_for_number(int number) {
    vector<int> num_operations(number + 1, 0);
    num_operations[1] = 0;
    for (int i = 2; i < num_operations.size(); ++i) {
        num_operations[i] = num_operations[i - 1] + 1;
        if (i % 2 == 0)
            num_operations[i] = min(num_operations[i], num_operations[i / 2] + 1);
        if (i % 3 == 0)
            num_operations[i] = min(num_operations[i], num_operations[i / 3] + 1);
    }
    return backtrack(num_operations, number);
}

int main() {
    int number;
    cin >> number;
    auto path = get_path_for_number(number);
    cout << path.size() - 1 << endl;
    for (auto &i : path)
        cout << i << " ";
}