#include <mutex>

using namespace std;

template<class T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value(initial) {}

    struct Access {
        T &ref_to_value;
        lock_guard<mutex> lock;
    };

    Access GetAccess() {
        return {value, lock_guard(m)};
    }

private:
    T value;
    mutex m;
};