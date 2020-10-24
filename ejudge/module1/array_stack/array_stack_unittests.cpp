// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <array_stack.h>

TEST(ArrayStack, Test) {
    Stack<int> stack(5);

    EXPECT_EQ(stack.pop(), "underflow\n");

    EXPECT_EQ(stack.push(1), "");
    EXPECT_EQ(stack.push(2), "");
    EXPECT_EQ(stack.push(3), "");
    EXPECT_EQ(stack.push(4), "");
    EXPECT_EQ(stack.push(5), "");

    EXPECT_EQ(stack.print(), "1 2 3 4 5\n");

    EXPECT_EQ(stack.push(6), "overflow\n");
    EXPECT_EQ(stack.pop(), "");
    EXPECT_EQ(stack.push(6), "");

    EXPECT_EQ(stack.print(), "1 2 3 4 6\n");
}
