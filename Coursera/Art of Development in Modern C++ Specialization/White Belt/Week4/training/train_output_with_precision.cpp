#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream input("input.txt");
    string str;
    cout << fixed << setprecision(3);
    while(getline(input, str)) {
        double d = stod(str);
        cout << d << endl;
    }
}