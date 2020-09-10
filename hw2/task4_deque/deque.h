// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW2_DEQUE_H_
#define HW2_DEQUE_H_

template <typename T>
class Deque {
private:
    struct Node {
        Node* Next;
        Node* Prev;

        T Value;
    };

private:
    Node* _head;
    Node* _tail;
    size_t _size;

public:
    Deque()
      : _head{nullptr}
      , _tail{nullptr}
      , _size{0}
    {}

    void push_front(const T& value) {
        auto newNode = new Node{nullptr, nullptr, value};

        if (empty()) {
            _head = newNode;
            _tail = newNode;
        } else {
            newNode->Next = _head;
            _head->Prev = newNode;
            _head = newNode;
        }

        ++_size;
    }
    void push_back(const T& value) {
        auto newNode = new Node{nullptr, nullptr, value};

        if (empty()) {
            _head = newNode;
            _tail = newNode;
        } else {
            newNode->Prev = _tail;
            _tail->Next = newNode;
            _tail = newNode;
        }

        ++_size;
    }

    T pop_front() {
        if (empty()) {
            throw std::length_error{
                "popped from empty deque"
            };
        }

        T value = _head->Value;

        if (size() == 1) {
            delete _head;
            _head = _tail = nullptr;
        } else {
            auto node = _head;

            _head = _head->Next;
            _head->Prev = nullptr;

            delete node;
        }

        --_size;

        return value;
    }
    T pop_back() {
        if (empty()) {
            throw std::length_error{
                    "popped from empty deque"
            };
        }

        T value = _tail->Value;

        if (size() == 1) {
            delete _tail;
            _head = _tail = nullptr;
        } else {
            auto node = _tail;

            _tail = _tail->Prev;
            _tail->Next = nullptr;

            delete node;
        }

        --_size;

        return value;
    }

    const T& front() const {
        if (empty()) {
            throw std::length_error{
                    "front() from empty deque"
            };
        }

        return _head->Value;
    }

    const T& back() const {
        if (empty()) {
            throw std::length_error{
                    "back() from empty deque"
            };
        }

        return _tail->Value;
    }

    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }
};

#endif // HW2_DEQUE_H_
