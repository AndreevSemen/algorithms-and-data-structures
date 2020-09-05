// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include "exponentiation.h"

double exponentiation(double x, size_t n) {
    if (n == 0) {
        return 1;
    }

    double square;
    if (n % 2 == 0) {
        square = exponentiation(x, n/2);
        return square*square;
    } else {
        square = exponentiation(x, (n-1)/2);
        return square*square * x;
    }
}
