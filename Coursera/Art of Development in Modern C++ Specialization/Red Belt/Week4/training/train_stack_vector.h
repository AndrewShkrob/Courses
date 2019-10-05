#pragma once

#include <array>

using namespace std;

template<typename T, size_t capacity>
class StackVector {
public:
    using sv_iterator = typename array<T, capacity>::iterator;
    using sv_const_iterator = typename array<T, capacity>::const_iterator;

    explicit StackVector(size_t a_size = 0) : size(a_size) {
        if (a_size > capacity)
            throw invalid_argument("size > capacity");
    }

    T &operator[](size_t index) {
        return arr[index];
    }

    const T &operator[](size_t index) const {
        return arr[index];
    }

    sv_iterator begin() {
        return arr.begin();
    }

    sv_iterator end() {
        return arr.begin() + size;
    }

    sv_const_iterator begin() const {
        return arr.begin();
    }

    sv_const_iterator end() const {
        return arr.begin() + size;
    }

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return capacity;
    }

    void PushBack(const T &value) {
        if (size == capacity)
            throw overflow_error("Full");
        arr[size++] = value;
    }

    T PopBack() {
        if (size == 0)
            throw underflow_error("Empty");
        return arr[--size];
    }

private:
    size_t size;
    array<T, capacity> arr;
};
