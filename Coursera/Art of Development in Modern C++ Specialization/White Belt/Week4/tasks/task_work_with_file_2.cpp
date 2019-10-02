#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string str;
    while(getline(input, str)) {
        output << str << endl;
    }
}