// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <chrono>

#include <permutation.h>

// Pay your attention!!!!!
// Only 10 times (on 10 input 10! = 3628800)
const size_t benchNum = 10;

struct Case {
    std::vector<size_t> Input;
    std::vector<std::vector<size_t>> Output;

    void RunIterative() const {
        using namespace iterative;
        EXPECT_EQ(Output, all_permutations(Input.begin(), Input.end()));
    }

    void RunRecursive() const {
        using namespace recursive;
        EXPECT_EQ(Output, all_permutations(Input.begin(), Input.end()));
    }
};

const std::vector<Case> cases = {
        { // Empty case
            {},
            {{}},
        },
        { // Single permutation case
            {1},
            {{1}},
        },
        { // The most simple common case
            {1, 2},
            {{1,2}, {2,1}}
        },
        {
            {1,2, 3},
            {
                {1,2,3},{1,3,2},
                {2,1,3},{2,3,1},
                {3,1,2},{3,2,1}
            },
        },
};

TEST(Permutation, Iterative) {
    for (const auto& c : cases) {
        c.RunIterative();
    }

    const Case inconsequentCase = { // Not sequenced input
            {3, 1, 2},
            {
                {3,1,2},{3,2,1},
                {1,2,3},{1,3,2},
                {2,1,3},{2,3,1},
            },
    };
    inconsequentCase.RunIterative();
}

TEST(Permutation, Recursive) {
    for (const auto& c : cases) {
        c.RunRecursive();
    }
}

TEST(Permutation, Bench) {
    typedef std::vector<size_t> Permutation;
    std::vector<Permutation> benches;
    benches.reserve(benchNum);
    for (size_t i = 0; i < benchNum; ++i) {
        benches.emplace_back(Permutation(i));
        std::iota(benches.back().begin(), benches.back().end(), 0);
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;

    // Iterative permutations
    start  = std::chrono::high_resolution_clock::now();
    for (const auto& bench : benches) {
        iterative::all_permutations(bench.begin(), bench.end());
    }
    finish = std::chrono::high_resolution_clock::now();
    auto iterativeDur = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    start  = std::chrono::system_clock::now();
    for (const auto& bench : benches) {
        recursive::all_permutations(bench.begin(), bench.end());
    }
    finish = std::chrono::system_clock::now();
    auto recursiveDur = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "iterative duration : " << iterativeDur.count() << std::endl;
    std::cout << "recursive duration : " << recursiveDur.count() << std::endl;
}
