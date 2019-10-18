#include <bits/stdc++.h>

using namespace std;

template<typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        lock_guard<mutex> lockGuard;
        V &ref_to_value;

        Access(const K &key, pair<mutex, map<K, V>> &p) : lockGuard(p.first), ref_to_value(p.second[key]) {}
    };

    explicit ConcurrentMap(size_t bucket_count) : bucket_count(bucket_count), maps(bucket_count) {}

    Access operator[](const K &key) {
        auto bucket = GetBucket(key);
        return Access(key, maps[bucket]);
    }

    map<K, V> BuildOrdinaryMap() {
        map<K, V> result_map;
        for (auto &[mtx, map] : maps) {
            lock_guard lock(mtx);
            result_map.insert(map.begin(), map.end());
        }
        return result_map;
    }

private:
    size_t bucket_count;
    vector<pair<mutex, map<K, V>>> maps;

    size_t GetBucket(const K &key) {
        return key % bucket_count;
    }
};