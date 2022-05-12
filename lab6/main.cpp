//Created by Artemida Zhuykova

#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock-actions.h>
#include "Tests/AVLTree.h"

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

