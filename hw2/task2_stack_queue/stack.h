// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW2_STACK_H_
#define HW2_STACK_H_

#include <forward_list>

template <typename T>
class Stack {
private:
    std::forward_list<T> _list;

public:
    void push(const T& value) {
        _list.push_front(value);
    }

    T pop() {
        T poped = _list.front();
        _list.pop_front();

        return poped;
    }

    bool empty() const {
        return _list.empty();
    }
};

#endif // HW2_STACK_H_
