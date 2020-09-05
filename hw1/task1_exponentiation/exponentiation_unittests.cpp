// Copyright 2020 AndreevSemen

#include <gtest/gtest.h>
#include <exponentiation.h>

#include <vector>
#include <chrono>

const size_t benchNum = 100000;

double slowExponentiation(double x, size_t n) {
    double result = 1;
    for (size_t i = 0; i < n; ++i) {
        result *= x;
    }
    return result;
}

struct Case {
    double x;
    size_t n;
    double Expected;

    void RunFast() const {
        EXPECT_FLOAT_EQ(Expected, exponentiation(x, n));
    }

    void RunSlow() const {
        EXPECT_FLOAT_EQ(Expected, slowExponentiation(x, n));
    }
};


TEST(Exponentiation, Test) {
    std::vector<Case> cases = {
            { // Even n
                2,
                10,
                1024,
            },
            { // Odd n
                2,
                7,
                128,
            },
            { // Another base
                3,
                4,
                81,
            },
            { // Zero n
                123456,
                0,
                1,
            },
            { // Negative base, even n
                -2,
                4,
                16,
            },
            { // Negative base, odd n
                -3,
                5,
                -243
            },
            { // Zero base
                0,
                128,
                0,
            },
            { // Zero base, zero n
                0,
                0,
                1
            },
    };

    for (const auto& c : cases) {
        c.RunFast();
    }
}

TEST(Exponentiation, Bench) {
    // Preparing data
    std::vector<Case> cases;
    for (size_t i = 0; i < benchNum; ++i) {
        cases.push_back(Case{
            double(i),
            i,
            pow(i, i),
        });
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;

    start  = std::chrono::high_resolution_clock::now();
    for (const auto& c : cases) {
        c.RunSlow();
    }
    finish = std::chrono::high_resolution_clock::now();
    auto slowDur = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    start  = std::chrono::system_clock::now();
    for (const auto& c : cases) {
        c.RunFast();
    }
    finish = std::chrono::system_clock::now();
    auto fastDur = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    EXPECT_GT(slowDur.count(), fastDur.count());
    std::cout << "slow duration : " << slowDur.count() << std::endl;
    std::cout << "fast duration : " << fastDur.count() << std::endl;
}
