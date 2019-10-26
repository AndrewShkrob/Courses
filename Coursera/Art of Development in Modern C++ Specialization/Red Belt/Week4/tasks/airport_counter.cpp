#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
#include <set>

using namespace std;

template<typename TAirport>
class AirportCounter {
private:
    static const size_t _size = static_cast<size_t>(TAirport::Last_);
public:
    AirportCounter() {
        for (size_t i = 0; i < _size; i++) {
            airport_count[i].first = static_cast<TAirport>(i);
        }
    }

    template<typename TIterator>
    AirportCounter(TIterator begin, TIterator end) : AirportCounter() {
        for_each(begin, end, [&](TAirport airport) { Insert(airport); });
    }

    size_t Get(TAirport airport) const {
        return airport_count[GetPosition(airport)].second;
    }

    void Insert(TAirport airport) {
        auto pos = GetPosition(airport);
        ++(airport_count[pos].second);
    }

    void EraseOne(TAirport airport) {
        auto &count = airport_count[GetPosition(airport)].second;
        if (count != 0)
            --count;
    }

    void EraseAll(TAirport airport) {
        airport_count[GetPosition(airport)].second = 0;
    }

    using Item = pair<TAirport, size_t>;
    using Items = array<Item, _size>;

    const Items &GetItems() const {
        return airport_count;
    }

private:
    array<Item, _size> airport_count;

    size_t GetPosition(TAirport airport) const {
        return static_cast<size_t>(airport);
    }
};
