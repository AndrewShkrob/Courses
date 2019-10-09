#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

template<typename T>
class SimpleVector {
public:
    SimpleVector() : _capacity(initial_capacity), _size(0), array(new T[initial_capacity]) {}

    explicit SimpleVector(size_t size) : _capacity(size), _size(size), array(new T[size]) {}

    ~SimpleVector() {
        delete[] array;
    }

    T &operator[](size_t index) {
        return array[index];
    }

    T *begin() {
        return array;
    }

    T *end() {
        return array + _size;
    }

    size_t Size() const {
        return _size;
    }

    size_t Capacity() const {
        return _capacity;
    }

    void PushBack(const T &value) {
        if (_size == _capacity)
            realloc();
        array[_size++] = value;
    }

private:
    const double coeff = 1.5;
    const size_t initial_capacity = 0;
    size_t _capacity;
    size_t _size;
    T *array;

    void realloc() {
        size_t new_capacity = static_cast<size_t>(coeff * _capacity + 1);
        T *new_arr = new T[new_capacity];
        copy(begin(), end(), new_arr);
        delete[] array;
        array = new_arr;
        _capacity = new_capacity;
    }
};