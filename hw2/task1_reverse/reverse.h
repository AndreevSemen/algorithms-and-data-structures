// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW2_REVERSE_H_
#define HW2_REVERSE_H_

#include <forward_list>
#include <memory>

template <typename T>
class List {
private:
    struct Node {
        Node* Next;
        T     Value;
    };

public:
    class Iterator {
        friend class List;

    private:
        Node* _ptr;

    public:
        Iterator(Node* ptr)
          : _ptr(ptr)
        {}

        Iterator operator++() {
            return Iterator{++_ptr};
        }

        Iterator operator--() {
            return Iterator{--_ptr};
        }

        operator bool() {
            return !_ptr;
        }
    };

private:
    Node*  _head;
    size_t _size;

public:
    List()
      : _head{nullptr}
      , _size{0}
    {}

    ~List() {
        while (_head != nullptr) {
            auto oldHead = _head;
            _head = _head->Next;
            delete oldHead;
        }
    }

    Iterator begin() {
        return Iterator{_head};
    }
    Iterator end() {
        if (_head == nullptr) {
            return Iterator{nullptr};
        }

        Node* tail = _head;
        while (tail->Next != nullptr) {
            tail = tail->Next;
        }

        return Iterator{tail};
    }

    void insert(Iterator pos, T value) {
        Node* newNode = new Node{nullptr, value};
        if (pos._ptr == nullptr) {
            newNode->Next = _head;
            _head = newNode;
        } else {
            newNode->Next = pos._ptr->Next;
            pos._ptr->Next = newNode;
        }

        ++_size;
    }

    void erase(Iterator pos) {
        Node* node = pos._ptr;
        Node* prev = _head;

        if (node == _head) {
            _head = _head->Next;
        } else {
            while (prev->Next != node) {
                prev = prev->Next;
            }
            prev->Next = node->Next;
        }

        delete node;
        --_size;
    }

    void reverse() {
        if (_size  == 0) {
            return;
        }

        Node* prev = nullptr;
        Node* curr = _head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->Next;
            curr->Next = prev;
            prev = curr;
            curr = next;
        }

        _head = prev;
    }

    bool operator==(const List& other) const {
        if (_size != other._size) {
            return false;
        }

        if (_size == 0) {
            return true;
        }

        for (auto this_node = _head, other_node = other._head;
             this_node != nullptr;
             this_node = this_node->Next, other_node = other_node->Next) {
            if (this_node->Value != other_node->Value) {
                return false;
            }
        }

        return true;
    }
};

template < typename T >
bool operator==(const List<T>& lhs, const List<T>& rhs) {
    return lhs == rhs;
}

#endif // HW2_REVERSE_H_
