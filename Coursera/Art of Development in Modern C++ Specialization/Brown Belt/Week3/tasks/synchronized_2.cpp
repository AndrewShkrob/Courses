#include <mutex>

using namespace std;

template<typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value(move(initial)) {}

    template<class Type>
    struct Access {
        Type ref_to_value;
        std::lock_guard<std::mutex> lock;
    };

    Access<T &> GetAccess() {
        return {value, std::lock_guard(m)};
    }

    Access<const T &> GetAccess() const {
        return {value, std::lock_guard(m)};
    }

private:
    T value;
    mutable std::mutex m;
};