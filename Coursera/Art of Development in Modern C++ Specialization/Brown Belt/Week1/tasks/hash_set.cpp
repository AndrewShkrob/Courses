#include <forward_list>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

template<typename Type, typename Hasher>
class HashSet {
public:
    using BucketList = forward_list<Type>;

public:
    explicit HashSet(size_t num_buckets, const Hasher &hasher = {})
            : num_buckets(num_buckets), hasher(hasher),
              container(num_buckets) {}

    void Add(const Type &value) {
        if (Has(value))
            return;
        auto &bucket = container[GetBucketIndex(value)];
        bucket.push_front(value);
    }

    bool Has(const Type &value) const {
        auto &bucket = container[GetBucketIndex(value)];
        return find(begin(bucket), end(bucket), value) != end(bucket);
    }

    void Erase(const Type &value) {
        auto &bucket = container[GetBucketIndex(value)];
        bucket.remove(value);
    }

    const BucketList &GetBucket(const Type &value) const {
        return container.at(GetBucketIndex(value));
    }

private:
    const size_t num_buckets;
    const Hasher &hasher;

    vector<BucketList> container;

    size_t GetBucketIndex(const Type &value) const {
        return hasher(value) % num_buckets;
    }
};
