// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include "fibonacci.h"

class QMatrix {
private:
    std::array<std::array<size_t, 2>, 2> _data;

public:
    QMatrix()
      : _data({
          std::array<size_t, 2>{1, 1},
          std::array<size_t, 2>{1, 0},
      })
    {}

    size_t at(size_t i, size_t j) const {
        if (i > 1 || j > 1) {
            throw std::out_of_range{
                "invalid indexes: i="+std::to_string(i)+", j="+std::to_string(j)
            };
        }

        return _data[i][j];
    }

    static const QMatrix& Q() {
        static QMatrix Q;
        return Q;
    }

    QMatrix operator*(const QMatrix& other) const {
        QMatrix r = *this;
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                size_t sum = 0;
                for (size_t k = 0; k < 2; k++) {
                    sum += _data[i][k] * other._data[k][j];
                }
                r._data[i][j] = sum;
            }
        }

        return r;
    }

    QMatrix operator^(size_t N) const {
        if (N == 0) {
            return Q();
        }
        if (N == 1) {
            return *this;
        }
        if (N == 2) {
            return *this * *this;
        }

        if (N % 2 == 0) {
            return (*this^(N/2))^2;
        } else {
            return (*this^(N-1)) * *this;
        }
    }
};

size_t fibonacci(size_t N) {
    if (N == 0) {
        return 0;
    }
    return (QMatrix::Q()^(N-1)).at(0, 0);
}
