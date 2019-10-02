#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream input("input.txt");
    int n;
    int m;
    input >> n >> m;
    vector<int> nums;
    for (int i = 0; i < n * m; i++) {
        int tmp;
        input >> tmp;
        input.ignore(1);
        nums.push_back(tmp);
    }

    for (int i = 0; i < nums.size(); i++) {
        cout << setw(10) << nums[i];
        if (i + 1 == n * m)
            break;
        if ((i + 1) % m == 0)
            cout << endl;
        else
            cout << " ";
    }
}