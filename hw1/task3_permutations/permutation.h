// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW1_PERMUTATION_H_
#define HW1_PERMUTATION_H_

#include <vector>
#include <numeric>

namespace iterative {

size_t factorial(size_t N) {
    if (N == 0 || N == 1) {
        return 1;
    }
    return N*factorial(N - 1);
}

template <typename BidirIter>
void do_next_permutation(BidirIter first, BidirIter last) {
    if (std::distance(first, last) < 2) {
        return;
    }

    auto pivot = last - 2;
    while (*(pivot) > *(pivot + 1)) {
        --pivot;

        if (pivot < first) {
            std::reverse(first, last);
            return;
        }
    }

    auto newPivot = pivot;
    auto i = pivot;
    while (i != last) {
        if (*i > *pivot) {
            newPivot = i;
        }
        ++i;
    }

    std::iter_swap(pivot, newPivot);
    std::reverse(pivot + 1, last);
}

template <typename BidirIter>
std::vector<std::vector<typename BidirIter::value_type>>
all_permutations(BidirIter first, BidirIter last) {
    typedef std::vector<typename BidirIter::value_type>
            Permutation;

    if (std::distance(first, last) < 0) {
        throw std::invalid_argument{
            "input range is invalid: last > first"
        };
    }

    auto pos = Permutation(first, last);

    std::vector<Permutation> permutes(factorial(std::distance(first, last)));
    for (auto& permute : permutes) {
        permute = pos;
        do_next_permutation(pos.begin(), pos.end());
    }

    return permutes;
}
} // namespace iterative


namespace recursive {

template <typename BidirIter>
std::vector<std::vector<typename BidirIter::value_type>>
all_permutations(BidirIter first, BidirIter last) {
    typedef std::vector<typename BidirIter::value_type>
            Permutation;

    if (std::distance(first, last) < 0) {
        throw std::invalid_argument{
                "input range is invalid: last > first"
        };
    }

    if (std::distance(first, last) == 0) {
        return std::vector<Permutation>{
            Permutation{},
        };
    }

    if (std::distance(first, last) == 1) {
        return std::vector<Permutation>{
            Permutation{*first},
        };
    }

    std::vector<Permutation> all;
    for (auto it = first; it != last; ++it) {
        // Exclude `it` from range
        Permutation permute(first, it);
        permute.insert(permute.end(), it + 1, last);

        std::vector<Permutation> sub = all_permutations(permute.begin(), permute.end());
        for (auto& subPermute : sub) {
            subPermute.insert(subPermute.begin(), *it);
            all.push_back(subPermute);
        }
    }

    return all;
}
} // namespace recursive

#endif // HW1_PERMUTATION_H_
