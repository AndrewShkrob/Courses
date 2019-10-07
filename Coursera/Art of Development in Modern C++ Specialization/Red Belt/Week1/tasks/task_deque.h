#pragma once

#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
class Deque {
public:
    Deque() = default;

    bool Empty() const {
        return size == 0;
    }

    size_t Size() const {
        return size;
    }

    T &operator[](size_t index) {
        const auto first_part_size = first_part.size();
        if (index < first_part_size)
            return first_part[first_part_size - index - 1];
        else
            return second_part[index - first_part_size];
    }

    const T &operator[](size_t index) const {
        const auto first_part_size = first_part.size();
        if (index < first_part_size)
            return first_part[first_part_size - index - 1];
        else
            return second_part[index - first_part_size];
    }

    const T &At(size_t index) const {
        if (index >= size)
            throw out_of_range("incorrect index");
        return operator[](index);
    }

    T &At(size_t index) {
        if (index >= size)
            throw out_of_range("incorrect index");
        return operator[](index);
    }

    void PushBack(const T &item) {
        second_part.push_back(item);
        size++;
    }

    void PushFront(const T &item) {
        first_part.push_back(item);
        size++;
    }

    const T &Back() const {
        if (second_part.empty())
            return first_part.front();
        else
            return second_part.back();
    }

    T &Back() {
        if (second_part.empty())
            return first_part.front();
        else
            return second_part.back();
    }

    const T &Front() const {
        if (first_part.empty())
            return second_part.front();
        else
            return first_part.back();
    }

    T &Front() {
        if (first_part.empty())
            return second_part.front();
        else
            return first_part.back();
    }

private:
    size_t size = 0;
    vector<T> first_part;
    vector<T> second_part;
};