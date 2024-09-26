#include <iostream>
#include <vector>
#include <map>
#include "../lib/Functions.h"

int main() {
    std::vector<long> numbers = {1, 2, 3, 4, 5};
    auto cont1 = numbers | transform([](long i) { return i * 2; });
    for (auto x: cont1) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    auto cont2 = cont1 | filter([](int i) { return i % 2 == 0; });
    for (auto x: cont2) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    auto cont3 = take(cont2, 3);
    for (auto x: cont3) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    auto cont4 = drop(cont3, 1);
    for (auto x: cont4) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    auto cont5 = reverse(cont4);
    for (auto x: cont5) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::map<int, std::string> map = {{1, "one"},
                                      {2, "two"},
                                      {3, "three"}};
    auto key = keys(map);
    for (auto x: key) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    auto vals = values(map) | filter([](const std::string &i) { return i == "one"; });
    for (const auto &x: vals) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}