#include <functional>

using namespace std;

template<typename T>
class LazyValue {
public:
    explicit LazyValue(std::function<T()> init) : init_function(move(init)) {}

    bool HasValue() const {
        return object.has_value();
    }

    const T &Get() const {
        if (!object.has_value())
            object = init_function();
        return *object;
    }

private:
    const std::function<T()> init_function;
    mutable optional<T> object;
};