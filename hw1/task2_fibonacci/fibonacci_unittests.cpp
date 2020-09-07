// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <chrono>

#include <fibonacci.h>

const size_t benchNum = 100000;

size_t slowFibonacci(size_t N) {
    size_t N1 = 0;
    size_t N2 = 1;

    for (size_t i = 0; i < N; ++i) {
        size_t newN = N1 + N2;
        N1 = N2;
        N2 = newN;
    }

    return N1;
}

struct Case {
    size_t N;
    size_t Expected;

    void RunFast() const {
        EXPECT_EQ(Expected, fibonacci(N));
    }

    void RunSlow() const {
        EXPECT_EQ(Expected, slowFibonacci(N));
    }
};

TEST(Fibonacci, OkTest) {
    std::vector<Case> cases = {
            {1, 1},
            {2, 1},
            {3, 2},
            {4, 3},
            {5, 5},
            {6, 8},
            {7, 13},
            {8, 21},
            {9, 34},
            {10, 55},
    };

    for (const auto& c : cases) {
        c.RunFast();
    }
}

TEST(Fibonacci, Bench) {
    // Preparing data
    std::vector<Case> cases;
    for (size_t i = 0; i < benchNum; ++i) {
        cases.push_back(Case{
                i,
                fibonacci(i),
        });
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;

    start  = std::chrono::high_resolution_clock::now();
    for (const auto& c : cases) {
        c.RunSlow();
    }
    finish = std::chrono::high_resolution_clock::now();
    auto slowDur = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    start  = std::chrono::system_clock::now();
    for (const auto& c : cases) {
        c.RunFast();
    }
    finish = std::chrono::system_clock::now();
    auto fastDur = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    EXPECT_GT(slowDur.count(), fastDur.count());
    std::cout << "slow duration : " << slowDur.count() << std::endl;
    std::cout << "fast duration : " << fastDur.count() << std::endl;
}
