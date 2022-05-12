#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <vector>
#include "CircularBuffer.h"

#define callAssert(...) assert(assertPrint(__VA_ARGS__))

template <auto& out=std::cout, typename T>
void print(const T& t)
{
    out << t << std::endl;
}

template<auto& out, class T, class... Args>
void print(const T& el, Args... args)
{
    out << el << " ";
    print<out>(args...);
}


template<class P, class... Args>
bool assertPrint(const P& pred, Args&&... args) {
    if (!pred(std::forward<Args>(args)...)) {
        print<std::cerr>(std::forward<Args>(args)...);
        return false;
    }
    return true;
}

std::stringstream ss;

int main() {
    std::vector<int> test{1, 2, 4, 5, 6, 9};

    CircularBuffer<int> c(7);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);
    c.push_back(5);
    c.push_back(6);
    c.push_back(7);

    std::cout << c.first() << std::endl;
    std::cout << c.last() << std::endl;

    c.push_front(1000);

    std::cout << c.first() << std::endl;
    std::cout << c.last() << std::endl;

    std::cout << *(c.begin() + 1) << std::endl;
    std::sort(c.begin(), c.end());

    std::upper_bound(c.begin(), c.end(), 4);

}
