#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    if (b == 0) {
        std::cout << "Impossible";
        return 0;
    }
    std::cout << a / b;
    return 0;
}
