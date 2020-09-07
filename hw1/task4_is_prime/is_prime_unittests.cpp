// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

// #pragma optimize( "[optimization-list]", off )

#include <gtest/gtest.h>

#include <chrono>

#include <is_prime.h>

const size_t benchNum = 100000000;

bool is_prime_slow(size_t N) {
    if (N == 0 || N == 1) {
        return false;
    }
    for (size_t i = 2; i < N; ++i) {
        if (N % i == 0) {
            return false;
        }
    }
    return true;
}

struct Case {
    size_t Input;
    bool   Expected;

    void RunSlow() const {
        EXPECT_EQ(Expected, is_prime_slow(Input))  << "slow in " << Input;
    }

    void RunFast() const {
        EXPECT_EQ(Expected, is_prime(Input)) << "fast in " << Input;
    }
};

const std::vector<Case> cases = {
        {0,  false},
        {1,  false},
        {2,  true},
        {3,  true},
        {4,  false},
        {5,  true},
        {6,  false},
        {7,  true},
        {8,  false},
        {9,  false},
        {10, false},
        {11, true},
        {12, false},
        {13, true},
        {14, false},
        {15, false},
        {16, false},
        {17, true},
        {18, false},
        {19, true},
        {20, false},
        {21, false},
        {22, false},
        {23, true},
        {24, false},
        {25, false},
        {26, false},
        {27, false},
        {28, false},
        {29, true},
        {30, false},
        {31, true},
        {32, false},
        {33, false},
        {34, false},
        {35, false},
        {36, false},
        {37, true},
        {38, false},
        {39, false},
        {40, false},
        {41, true},
};

TEST(IsPrime, Test) {
    for (const auto& c : cases) {
        c.RunFast();
    }
}

TEST(IsPrime, Bench) {
    std::vector<Case> cases(benchNum);
    for (size_t i = 0; i < 0; ++i) {
        cases[i] = Case{
            i,
            is_prime(i),
        };
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;

    start = std::chrono::high_resolution_clock::now();
    for (const auto& c : cases) {
        c.RunSlow();
    }
    finish = std::chrono::high_resolution_clock::now();
    auto slowDur = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);


    start = std::chrono::high_resolution_clock::now();
    for (const auto& c : cases) {
        c.RunFast();
    }
    finish = std::chrono::high_resolution_clock::now();
    auto fastDur = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    

    EXPECT_GT(slowDur.count(), fastDur.count());
    std::cout << "slow duration : " << slowDur.count() << std::endl; // ~5108ms ???
    std::cout << "fast duration : " << fastDur.count() << std::endl; // ~5065ms ???
}
