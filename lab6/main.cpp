//Created by Artemida Zhuykova

#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock-actions.h>
#include "Tests/AVLTree.h"

template <int x> struct factor {};
template <int x> struct deg {};
template <int N> class value {
public:
    static constexpr int x = N;
};

template <typename Fac, typename Deg> class poly0;
template <int Fac, int Deg> class poly0<factor<Fac>, deg<Deg>> {
public:
    static constexpr int pow(int x, int N) {
        if(N < 0) return 1 / pow(x, -N);
        else if(N == 0) return 1;
        else if(N % 2 == 0){
            int p = pow(x, N / 2);
            return p * p;
        } else return pow(x, N - 1) * x;
    }
    static constexpr int at(int val) noexcept {return (int)(Fac * pow(val, Deg));}
};

template<typename ... T>
struct qq {
    static constexpr int val = 0;
};

template<int N, int Q, int M, typename ... kek>
struct qq<value<N>, poly0<factor<Q>, deg<M>>, kek ...> {
    static constexpr int val = poly0<factor<Q>, deg<M>>::at(N) + qq<value<N>, kek...>::val;
};

template<int N, int Q, int M>
struct qq<value<N>, poly0<factor<Q>, deg<M>>> {
    static constexpr int val = poly0<factor<Q>, deg<M>>::at(N);
};

int main(int argc, char *argv[]) {
    // 4x^2 + 3x + 10, point 20
    using ff = qq<
            value<10>,
            poly0<factor<9>, deg<3>>,
            poly0<factor<3>, deg<2>>,
            poly0<factor<2>, deg<1>>,
            poly0<factor<1>, deg<0>>
            >;
    std::cout << ff::val << std::endl;
    return RUN_ALL_TESTS();
}

