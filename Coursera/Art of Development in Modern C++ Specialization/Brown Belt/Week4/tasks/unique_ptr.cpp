#include <cstddef>
#include <utility>

using namespace std;

template<typename T>
class UniquePtr {
private:
    T *pointer = nullptr;

public:
    UniquePtr() {}

    UniquePtr(T *ptr) {
        pointer = ptr;
    }

    UniquePtr(const UniquePtr &ptr) = delete;

    UniquePtr(UniquePtr &&other) {
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr &operator=(nullptr_t) {
        delete pointer;
        pointer = nullptr;
        return *this;
    }

    UniquePtr &operator=(UniquePtr &&other) {
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    ~UniquePtr() {
        delete pointer;
    }

    T &operator*() const {
        return *pointer;
    }

    T *operator->() const {
        return pointer;
    }

    T *Release() {
        auto ptr = pointer;
        pointer = nullptr;
        return ptr;
    }

    void Reset(T *ptr) {
        delete pointer;
        pointer = ptr;
    }

    void Swap(UniquePtr &other) {
        swap(pointer, other.pointer);
    }

    T *Get() const {
        return pointer;
    }
};