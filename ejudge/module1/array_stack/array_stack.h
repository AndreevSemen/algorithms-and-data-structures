// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef ARRAY_STACK_H_
#define ARRAY_STACK_H_

#include <iostream>
#include <vector>

template <typename T>
class Stack {
private:
    size_t _capacity;
    size_t _size;
    std::vector<T> _data;

public:
    explicit Stack(size_t cap)
      : _capacity{cap}
      , _size{0}
      , _data{std::vector<T>(cap)}
    {}

    std::string push(T value) {
        if (_size == _capacity) {
            return overflow();
        } else {
            _data[_size++] = value;
        }
        return "";
    }

    std::string pop() {
        if (_size == 0) {
            return underflow();
        } else {
            --_size;
        }
        return "";
    }

    std::string print() const {
        std::string result;
        for (size_t i = 0; i < _size; ++i) {
            result += std::to_string(_data[i]);
            if (i != _size - 1) {
                result += ' ';
            }
        }
        return result + "\n";
    }

    static std::string underflow() {
        return "underflow\n";
    }

    static std::string overflow() {
        return "overflow\n";
    }
};

#endif // ARRAY_STACK_H_
