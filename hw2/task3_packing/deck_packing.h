// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW2_DECK_PACKING_H_
#define HW2_DECK_PACKING_H_

#include <algorithm>
#include <array>
#include <vector>
#include <random>

typedef uint8_t byte_t;

constexpr size_t deckSize = 52;
constexpr size_t byteSize = 8;

constexpr size_t suitPackBitSize = 2;
constexpr size_t valuePackBitSize = 4;

constexpr size_t suitsPackSize  = (deckSize * suitPackBitSize)/byteSize;
constexpr size_t valuesPackSize = (deckSize * valuePackBitSize)/byteSize;

constexpr size_t suitesPerByte = byteSize / suitPackBitSize;
constexpr size_t valuesPerByte = byteSize / valuePackBitSize;

typedef std::array<byte_t, suitsPackSize + valuesPackSize> Pack;

class Deck {
public:
    struct Card {
        enum SuitEnum {
            Spades   = 0,
            Clubs    = 1,
            Diamonds = 2,
            Hearts   = 3,
        };

        enum ValueEnum {
            Two   = 2,
            Tree  = 3,
            Four  = 4,
            Five  = 5,
            Six   = 6,
            Seven = 7,
            Eight = 8,
            Nine  = 9,
            Ten   = 10,
            Jack  = 11,
            Queen = 12,
            King  = 13,
            Ace   = 14,
        };

        SuitEnum  Suit;
        ValueEnum Value;

        bool operator==(const Card& other) const;
    };

private:
    std::vector<Card> _cards;

public:
    Deck();

    void shuffle();

    bool operator==(const Deck& other) const;

    Pack pack() const;

    static Deck unpack(const Pack& package);
};

#endif // HW2_DECK_PACKING_H_
