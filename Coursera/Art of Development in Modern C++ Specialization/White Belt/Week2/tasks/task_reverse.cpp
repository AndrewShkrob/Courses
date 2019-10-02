#include <bits/stdc++.h>

using namespace std;

void Reverse(vector<int> &vec) {
    for (int i = 0; 2 * i < vec.size(); i++)
        swap(vec[i], vec[vec.size() - 1 - i]);
}