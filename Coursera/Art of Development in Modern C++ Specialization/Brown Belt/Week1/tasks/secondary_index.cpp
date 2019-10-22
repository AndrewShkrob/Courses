#include <bits/stdc++.h>

using namespace std;

using Id = string;
using User = string;
using Timestamp = int;
using Karma = int;

struct Record {
    Id id;
    string title;
    User user;
    Timestamp timestamp;
    Karma karma;
};

class Database {
public:
    bool Put(const Record &record) {
        if (record_ref.find(record.id) != record_ref.end())
            return false;
        auto rec = new Record(record);
        record_ref[record.id] = rec;
        auto t_i = ranged_by_timestamp.emplace(record.timestamp, rec);
        auto k_i = ranged_by_karma.emplace(record.karma, rec);
        auto u_i = ranged_by_user.emplace(record.user, rec);
        record_iters[record.id] = tuple(t_i, k_i, u_i);
        return true;
    }

    const Record *GetById(const Id &id) const {
        if (record_ref.find(id) == record_ref.end())
            return nullptr;
        return record_ref.at(id);
    }

    bool Erase(const Id &id) {
        if (record_ref.find(id) == record_ref.end())
            return false;
        record_ref.erase(id);

        auto[t_i, k_i, u_i] = record_iters[id];
        ranged_by_user.erase(u_i);
        ranged_by_karma.erase(k_i);
        ranged_by_timestamp.erase(t_i);
        record_iters.erase(id);
        return true;
    }

    template<typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto begin = ranged_by_timestamp.lower_bound(low);
        auto end = ranged_by_timestamp.upper_bound(high);
        Loop(begin, end, callback);
    }

    template<typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto begin = ranged_by_karma.lower_bound(low);
        auto end = ranged_by_karma.upper_bound(high);
        Loop(begin, end, callback);
    }

    template<typename Callback>
    void AllByUser(const string &user, Callback callback) const {
        auto[begin, end] = ranged_by_user.equal_range(user);
        Loop(begin, end, callback);
    }

private:
    using t_iter = typename multimap<Timestamp, Record *>::iterator;
    using k_iter = typename multimap<Karma, Record *>::iterator;
    using u_iter = typename multimap<User, Record *>::iterator;

    unordered_map<Id, Record *> record_ref;
    unordered_map<Id, tuple<t_iter, k_iter, u_iter>> record_iters;
    multimap<Timestamp, Record *> ranged_by_timestamp;
    multimap<Karma, Record *> ranged_by_karma;
    multimap<User, Record *> ranged_by_user;

    template<class Iter, class Callback>
    void Loop(Iter begin, Iter end, Callback callback) const {
        while (begin != end) {
            auto &[key, rec] = *begin;
            if (!callback(*rec))
                break;
            ++begin;
        }
    }
};