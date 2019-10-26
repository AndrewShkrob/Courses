#include <shared_mutex>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
public:
    using MapType = unordered_map<K, V, Hash>;

    struct WriteAccess {
        unique_lock<shared_mutex> lock;
        V &ref_to_value;
    };

    struct ReadAccess {
        shared_lock<shared_mutex> lock;
        const V &ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count)
            : bucket_count(bucket_count),
              lockers(bucket_count),
              maps(bucket_count) {

    }

    WriteAccess operator[](const K &key) {
        auto bucket = GetBucket(key);
        auto &u_map = maps[bucket];
        return {unique_lock(lockers[bucket]), u_map[key]};
    }

    ReadAccess At(const K &key) const {
        auto bucket = GetBucket(key);
        auto &u_map = maps[bucket];
        return {shared_lock(lockers[bucket]), u_map.at(key)};
    }

    bool Has(const K &key) const {
        auto bucket = GetBucket(key);
        shared_lock lock(lockers[bucket]);
        auto &u_map = maps[bucket];
        return u_map.find(key) != end(u_map);
    }

    MapType BuildOrdinaryMap() const {
        MapType result_map;
        for (size_t i = 0; i < bucket_count; ++i) {
            shared_lock lock(lockers[i]);
            result_map.insert(begin(maps[i]), end(maps[i]));
        }
        return result_map;
    }

private:
    Hash hasher;
    size_t bucket_count;
    mutable vector<shared_mutex> lockers;
    vector<MapType> maps;

    size_t GetBucket(const K &key) const {
        return hasher(key) % bucket_count;
    }
};
