// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef HW2_REMOVE_SEQUENCES_H_
#define HW2_REMOVE_SEQUENCES_H_

template <typename T>
void remove_sequences(std::forward_list<T>& list) {
    if (std::distance(list.begin(), list.end()) == 0) {
        return;
    }

    auto iter1 = list.begin();
    auto iter2 = std::next(list.begin(), 1);

    while (iter2 != list.end()) {
        if (*iter1 == *iter2) {
            iter2 = list.erase_after(iter1);
        } else {
            ++iter1;
            ++iter2;
        }
    }
}

#endif // HW2_REMOVE_SEQUENCES_H_
