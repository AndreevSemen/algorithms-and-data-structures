// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <queue.h>

TEST(Queue, Test) {
    Queue<size_t> queue1;

    EXPECT_TRUE(queue1.empty());
    EXPECT_EQ(queue1.size(), 0);

    queue1.push(0);
    queue1.push(1);
    queue1.push(2);
    queue1.push(3);

    EXPECT_FALSE(queue1.empty());
    EXPECT_EQ(queue1.size(), 4);

    EXPECT_EQ(queue1.pop(), 0);
    EXPECT_EQ(queue1.pop(), 1);
    EXPECT_EQ(queue1.pop(), 2);
    EXPECT_EQ(queue1.pop(), 3);

    EXPECT_TRUE(queue1.empty());
    EXPECT_EQ(queue1.size(), 0);
}
