// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW2_QUEUE_H
#define HW2_QUEUE_H

#include <list>

template <typename T>
class Queue {
private:
    std::list<T> _list;

public:
    void push(const T& value) {
        _list.push_front(value);
    }

    T pop() {
        T poped = _list.back();
        _list.pop_back();

        return poped;
    }

    bool empty() const {
        return _list.empty();
    }

    size_t size() const {
        return _list.size();
    }
};

#endif // HW2_QUEUE_H_
