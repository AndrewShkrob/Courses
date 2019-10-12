#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<bool> queue;
    int n;
    cin >> n;
    while (n--) {
        string str;
        int x;
        cin >> str;
        if (str == "WORRY") {
            cin >> x;
            queue[x] = true;
        } else if (str == "QUIET") {
            cin >> x;
            queue[x] = false;
        } else if (str == "COME") {
            cin >> x;
            queue.resize(queue.size() + x, false);
        } else if (str == "WORRY_COUNT") {
            cout << count_if(queue.begin(), queue.end(), [](bool b) { return b; }) << " ";
        }
    }
}