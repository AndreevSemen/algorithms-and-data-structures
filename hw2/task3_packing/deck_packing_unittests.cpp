// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <deck_packing.h>

TEST(Packing, Test) {
    Deck deck;

    EXPECT_EQ(deck, Deck::unpack(deck.pack()));

    deck.shuffle();
    EXPECT_EQ(deck, Deck::unpack(deck.pack()));
}
