// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <is_prime.h>

bool is_prime(size_t N) {
    if (N == 1 || N == 0) {
        return false;
    }

    size_t bound = std::sqrt(N);
    for (size_t f = 2; f <= bound; ++f) {
        if (N % f == 0) {
            return false;
        }
    }
    return true;
}
