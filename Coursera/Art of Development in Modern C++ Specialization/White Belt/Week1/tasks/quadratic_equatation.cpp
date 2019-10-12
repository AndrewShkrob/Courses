#include <bits/stdc++.h>

using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    double d = b * b - 4 * a * c;
    double x1 = (-b - sqrt(d)) / (2 * a);
    double x2 = (-b + sqrt(d)) / (2 * a);
    if (d < 0 || (a == 0 && b == 0))
        return 0;
    if (a == 0)
        cout << -c / b;
    else if (fabs(x1 - x2) < std::numeric_limits<double>::epsilon())
        cout << x1;
    else
        cout << x1 << " " << x2;
    return 0;
}