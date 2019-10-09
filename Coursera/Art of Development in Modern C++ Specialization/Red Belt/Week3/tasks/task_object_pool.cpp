#include <bits/stdc++.h>

using namespace std;

template<class T>
class ObjectPool {
public:
    T *Allocate() {
        if (deallocated.empty()) {
            auto it = allocated.insert(new T);
            return *(it.first);
        }
        return alloc();
    }

    T *TryAllocate() {
        if (deallocated.empty())
            return nullptr;
        return alloc();
    }

    void Deallocate(T *object) {
        auto it = allocated.find(object);
        if (it == allocated.end())
            throw invalid_argument("deallocate");
        allocated.erase(it);
        deallocated.push(object);
    }

    ~ObjectPool() {
        for (T *object : allocated) {
            delete object;
        }
        while (!deallocated.empty()) {
            T *object = deallocated.front();
            deallocated.pop();
            delete object;
        }
    }

private:
    set<T *> allocated;
    queue<T *> deallocated;

    T *alloc() {
        auto obj = deallocated.front();
        deallocated.pop();
        auto it = allocated.insert(obj);
        return *(it.first);
    }
};
