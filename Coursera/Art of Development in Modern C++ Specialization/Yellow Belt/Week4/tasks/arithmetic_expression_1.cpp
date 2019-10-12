#include <bits/stdc++.h>

using namespace std;

int main() {
    int x, n;
    cin >> x >> n;
    stringstream ss;
    ss << string(n, '(') << to_string(x);
    while (n--) {
        ss << ")";
        char sym;
        int num;
        cin >> sym >> num;
        ss <<  " " << sym << " " << to_string(num);
    }

    cout << ss.str() << endl;
}