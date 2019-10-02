#include <bits/stdc++.h>

using namespace std;

int get_priority(char symbol) {
    switch (symbol) {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
    }
}

int main() {
    int x, n;
    cin >> x >> n;
    stringstream ss;
    ss << to_string(x);
    int last_priority = 2, amt = 0;
    while (n--) {
        char sym;
        int num, priority;
        cin >> sym >> num;
        priority = get_priority(sym);
        if (priority > last_priority) {
            amt++;
            ss << ")";
        }
        last_priority = priority;
        ss << " " << sym << " " << to_string(num);
    }

    cout << string(amt, '(') << ss.str() << endl;
}