#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using min_max = pair<ll, ll>;
using table = vector<vector<min_max>>;

ll min(ll a, ll b, ll c, ll d, ll e) {
    return min(a, min(b, min(c, min(d, e))));
}

ll max(ll a, ll b, ll c, ll d, ll e) {
    return max(a, max(b, max(c, max(d, e))));
}

ll calc(ll a, ll b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        default:
            return 0;
    }
}

min_max get_min_max(const table &t, int i, int j, const vector<char> &operators) {
    ll min_e = numeric_limits<ll>::max();
    ll max_e = numeric_limits<ll>::min();

    for (int k = i; k < j; ++k) {
        ll a = calc(t[i][k].first, t[k + 1][j].first, operators[k]);
        ll b = calc(t[i][k].first, t[k + 1][j].second, operators[k]);
        ll c = calc(t[i][k].second, t[k + 1][j].first, operators[k]);
        ll d = calc(t[i][k].second, t[k + 1][j].second, operators[k]);
        min_e = min(a, b, c, d, min_e);
        max_e = max(a, b, c, d, max_e);
    }
    return {min_e, max_e};
}

ll get_max_value(const vector<int> &operands, const vector<char> &operators) {
    table t(operands.size(), vector<min_max>(operands.size()));
    for (int i = 0; i < t.size(); i++)
        t[i][i] = {operands[i], operands[i]};
    for (int s = 1; s < t.size(); ++s) {
        for (int i = 0; i < t.size() - s; ++i) {
            int j = i + s;
            min_max mm = get_min_max(t, i, j, operators);
            t[i][j].first = mm.first;
            t[i][j].second = mm.second;
        }
    }
    return t[0].back().second;
}

int main() {
    string expression;
    cin >> expression;
    vector<int> operands;
    vector<char> operators;
    for (int i = 0; i < expression.size(); ++i) {
        if (i % 2 == 0)
            operands.push_back(expression[i] - '0');
        else
            operators.push_back(expression[i]);
    }
    cout << get_max_value(operands, operators);
}