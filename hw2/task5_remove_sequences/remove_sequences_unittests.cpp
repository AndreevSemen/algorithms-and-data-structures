// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <forward_list>

#include <remove_sequences.h>

TEST(RemoveSequences, Test) {
    std::forward_list<size_t> list1;
    std::forward_list<size_t> expected1 = {0, 1, 2, 1};

    ASSERT_NO_THROW(remove_sequences(list1));
    list1.push_front(0);
    auto it = list1.begin();
    it = list1.insert_after(it, 1);
    it = list1.insert_after(it, 1);
    it = list1.insert_after(it, 1);
    it = list1.insert_after(it, 2);
    it = list1.insert_after(it, 2);
    it = list1.insert_after(it, 1);
    ASSERT_NO_THROW(remove_sequences(list1));
    EXPECT_EQ(list1, expected1);
}
