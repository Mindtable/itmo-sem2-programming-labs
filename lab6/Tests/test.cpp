#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AVLTree.h"

using testing::Eq;

namespace {
    class ClassDeclaration : public testing::Test {
    public:
        ClassDeclaration() {

        }
    };
}

TEST_F(ClassDeclaration, test_delete) {
    int value = Polynomial<20, 4, 3, 10>::value;
    ASSERT_EQ(1670, value);
}

TEST_F(ClassDeclaration, test_multiple) {
    int value = Polynomial<20, 20, 239, 4, 3, 10>::value;
    ASSERT_NE(1670, value);
}



