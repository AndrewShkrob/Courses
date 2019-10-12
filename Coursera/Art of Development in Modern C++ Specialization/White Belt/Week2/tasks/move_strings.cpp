#include <bits/stdc++.h>

using namespace std;

void MoveStrings(vector<string> &source, vector<string> &dest) {
    copy(source.begin(), source.end(), back_inserter(dest));
    source.clear();
}