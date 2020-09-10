// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <deque.h>


TEST(Deque, Test) {
    Deque<size_t> deck;

    EXPECT_THROW(deck.front(), std::length_error);
    EXPECT_THROW(deck.back(), std::length_error);
    EXPECT_TRUE(deck.empty());
    EXPECT_EQ(deck.size(), 0);

    deck.push_front(0);
    EXPECT_EQ(deck.front(), 0);
    EXPECT_EQ(deck.back(), 0);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 1);

    EXPECT_EQ(deck.pop_front(), 0);
    EXPECT_THROW(deck.front(), std::length_error);
    EXPECT_THROW(deck.back(), std::length_error);
    EXPECT_TRUE(deck.empty());
    EXPECT_EQ(deck.size(), 0);

    deck.push_back(0);
    EXPECT_EQ(deck.front(), 0);
    EXPECT_EQ(deck.back(), 0);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 1);

    EXPECT_EQ(deck.pop_front(), 0);
    EXPECT_THROW(deck.front(), std::length_error);
    EXPECT_THROW(deck.back(), std::length_error);
    EXPECT_TRUE(deck.empty());
    EXPECT_EQ(deck.size(), 0);

    deck.push_back(0); // 0
    EXPECT_EQ(deck.front(), 0);
    EXPECT_EQ(deck.back(), 0);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 1);

    deck.push_front(1); // 1 0
    EXPECT_EQ(deck.front(), 1);
    EXPECT_EQ(deck.back(), 0);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 2);

    deck.push_back(2); // 1 0 2
    EXPECT_EQ(deck.front(), 1);
    EXPECT_EQ(deck.back(), 2);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 3);

    EXPECT_EQ(deck.pop_front(), 1); // 0 2
    EXPECT_EQ(deck.front(), 0);
    EXPECT_EQ(deck.back(), 2);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 2);

    EXPECT_EQ(deck.pop_back(), 2); // 0
    EXPECT_EQ(deck.front(), 0);
    EXPECT_EQ(deck.back(), 0);
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 1);

    EXPECT_EQ(deck.pop_back(), 0);
    EXPECT_THROW(deck.front(), std::length_error);
    EXPECT_THROW(deck.back(), std::length_error);
    EXPECT_TRUE(deck.empty());
    EXPECT_EQ(deck.size(), 0);

    EXPECT_THROW(deck.pop_front(), std::length_error);
    EXPECT_THROW(deck.pop_back(), std::length_error);
}
