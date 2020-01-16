#include <bits/stdc++.h>

using namespace std;

int main() {
    stack<int> st;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;
        if (command == "push") {
            int x;
            cin >> x;
            if (st.empty())
                st.push(x);
            else
                st.push(max(x, st.top()));
        } else if (command == "pop") {
            st.pop();
        } else {
            cout << st.top() << endl;
        }
    }
}