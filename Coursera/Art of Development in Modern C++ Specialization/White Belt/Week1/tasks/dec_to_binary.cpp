#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    const vector<int> vec = {3, 4, 5};
    bitset<std::numeric_limits<int>::digits> num(n);
    string s = num.to_string();
    auto first_digit = s.find('1');
    if (first_digit != std::string::npos)
        std::cout << s.substr(first_digit);
    else
        std::cout << 0;
    return 0;
}