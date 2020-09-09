// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <reverse.h>

TEST(Reverse, Test) {
    List<size_t> list1;
    List<size_t> expected1;

    EXPECT_EQ(expected1, list1);

    list1.insert(list1.end(), 0);
    list1.insert(list1.end(), 1);
    list1.insert(list1.end(), 2);
    list1.insert(list1.end(), 3);
    list1.insert(list1.end(), 4);

    expected1.insert(expected1.end(), 4);
    expected1.insert(expected1.end(), 3);
    expected1.insert(expected1.end(), 2);
    expected1.insert(expected1.end(), 1);
    expected1.insert(expected1.end(), 0);

    EXPECT_NE(expected1, list1);

    list1.reverse();

    EXPECT_EQ(expected1, list1);
}
