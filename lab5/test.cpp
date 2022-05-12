#include "CustomAllocator.h"
#include <limits>
#include <vector>
#include <chrono>
#include <list>
#include <set>
#include <forward_list>

int main() {
    std::vector<int> test;
    for (int i = 0; i != 5'000; ++i) {
        test.push_back(i);
    }
    for (auto& elem: test) {
        elem *= 10;
    }

    for (const auto& elem: test) {
        std::cout << elem << std::endl;
    }
}