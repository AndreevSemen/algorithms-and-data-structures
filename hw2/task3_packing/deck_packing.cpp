// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <deck_packing.h>

bool Deck::Card::operator==(const Card& other) const {
    return Suit == other.Suit && Value == other.Value;
}

Deck::Deck() {
    for (size_t suit = 0; suit < 4; ++suit) {
        for (size_t value = 2; value < 15; ++value) {
            _cards.push_back(
                    Card{
                            Card::SuitEnum(suit),
                            Card::ValueEnum(value),
                    }
            );
        }
    }
}

void Deck::shuffle() {
    std::shuffle(_cards.begin(), _cards.end(),
                 std::mt19937(std::random_device()()));
}

bool Deck::operator==(const Deck& other) const {
    return _cards == other._cards;
}

Pack Deck::pack() const {
    Pack pack{byte_t{0}};

    for (size_t byte = 0; byte < suitsPackSize; ++byte) {
        byte_t packedByte = 0;
        for (size_t suit = 0; suit < suitesPerByte; ++suit) {

            byte_t packedSuit = _cards[byte*suitesPerByte + suit].Suit
                                << ((suitesPerByte - 1 - suit) * suitPackBitSize);
            packedByte |=  packedSuit;
        }

        pack[byte] = packedByte;
    }

    for (size_t byte = 0; byte < valuesPackSize; ++byte) {
        byte_t packedByte = 0;
        for (size_t value = 0; value < valuesPerByte; ++value) {
            byte_t packedValue = _cards[byte*valuesPerByte + value].Value
                                 << ((valuesPerByte - 1 - value) * valuePackBitSize);
            packedByte |= packedValue;
        }

        pack[suitsPackSize + byte] = packedByte;
    }

    return pack;
}

Deck Deck::unpack(const Pack& package) {
    Deck deck;

    size_t suitIndex = 0;
    byte_t suitByte = package[suitIndex];
    byte_t suitMask = (1 << suitPackBitSize) - 1; // 2^n - 1 (00000011)
    suitMask <<= (byteSize - suitPackBitSize);    // 11000000

    size_t valueIndex = suitsPackSize;
    byte_t valueByte = package[valueIndex];
    byte_t valueMask = (1 << valuePackBitSize) - 1; // 2^n - 1 (00001111)
    valueMask <<= (byteSize - valuePackBitSize);   // 11110000

    for (size_t card = 0; card < deck._cards.size(); ++card) {
        size_t suitPos  = card % suitesPerByte;
        size_t valuePos = card % valuesPerByte;

        if (card != 0 && suitPos == 0) {
            ++suitIndex;
            suitByte = package[suitIndex];
        }
        if (card != 0 && valuePos == 0) {
            ++valueIndex;
            valueByte = package[valueIndex];
        }

        auto currSuitMask  = (suitMask  >> (suitPackBitSize *(suitPos)));
        auto currValueMask = (valueMask >> (valuePackBitSize*(valuePos)));

        auto byteSuit  = suitByte & currSuitMask;
        auto byteValue = valueByte & currValueMask;

        byteSuit  >>= suitPackBitSize  * (suitesPerByte - 1 - suitPos);
        byteValue >>= valuePackBitSize * (valuesPerByte - 1 - valuePos);

        deck._cards[card] = Card{
            Card::SuitEnum(byteSuit),
            Card::ValueEnum(byteValue),
        };
    }

    return deck;
}
