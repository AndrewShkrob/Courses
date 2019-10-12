#include <bits/stdc++.h>

using namespace std;

template<typename T>
void Swap(T *first, T *second) {
    swap(*first, *second);
}

template<typename T>
void SortPointers(vector<T *> &pointers) {
    sort(pointers.begin(), pointers.end(), [](auto a, auto b) { return *a < *b; });
}

template<typename T>
void ReversedCopy(T *source, size_t count, T *destination) {
    T *tmp_arr = new T[count];
    for (size_t i = 0; i < count; i++)
        tmp_arr[i] = source[i];
    size_t pos = 0;
    while (pos != count) {
        destination[pos] = tmp_arr[count - 1 - pos];
        pos++;
    }
    delete[] tmp_arr;
}