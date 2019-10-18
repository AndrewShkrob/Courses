#include <bits/stdc++.h>

using namespace std;

template<typename T>
class PriorityCollection {
public:
    using Id = size_t;
    using Priority = int;

    Id Add(T object) {
        Id id = free_id++;
        Object obj{0, move(object)};
        object_pool[id] = move(obj);
        objects_by_priority.emplace(0, id);
        return id;
    }

    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        for (; range_begin != range_end; ++range_begin) {
            *ids_begin = Add(move(*range_begin));
            ++ids_begin;
        }
    }

    bool IsValid(Id id) const {
        return object_pool.find(id) != object_pool.end();
    }

    const T &Get(Id id) const {
        return object_pool.at(id).obj;
    }

    void Promote(Id id) {
        Object &obj = object_pool[id];
        auto pid_iter = objects_by_priority.find(pair(obj.priority, id));
        objects_by_priority.erase(pid_iter);
        obj.priority++;
        objects_by_priority.emplace(obj.priority, id);
    }

    pair<const T &, int> GetMax() const {
        auto pid_iter = prev(objects_by_priority.end());
        const Object &obj = object_pool.at(pid_iter->second);
        return pair<const T &, int>{obj.obj, obj.priority};
    }

    pair<T, int> PopMax() {
        auto pid_iter = prev(objects_by_priority.end());
        Object &obj = object_pool[pid_iter->second];
        pair<T, int> result{move(obj.obj), obj.priority};
        object_pool.erase(pid_iter->second);
        objects_by_priority.erase(pid_iter);
        return move(result);
    }

private:
    Id free_id = 0;
    struct Object {
        Priority priority;
        T obj;
    };

    set<pair<Priority, Id>> objects_by_priority;
    map<Id, Object> object_pool;
};