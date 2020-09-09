// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <stack.h>

TEST(Stack, Test) {
    Stack<size_t> stack1;

    EXPECT_TRUE(stack1.empty());

    stack1.push(0);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    EXPECT_FALSE(stack1.empty());

    EXPECT_EQ(stack1.pop(), 3);
    EXPECT_EQ(stack1.pop(), 2);
    EXPECT_EQ(stack1.pop(), 1);
    EXPECT_EQ(stack1.pop(), 0);

    EXPECT_TRUE(stack1.empty());
}
