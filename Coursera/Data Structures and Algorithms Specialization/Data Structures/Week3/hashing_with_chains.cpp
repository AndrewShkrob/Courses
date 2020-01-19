#include <bits/stdc++.h>

using namespace std;

struct Query {
    string type, s;
    size_t ind{};
};

class QueryProcessor {
    int bucket_count;

    vector<list<string>> elements;

    size_t hash_func(const string &s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count), elements(bucket_count, list<string>{}) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query &query) {
        if (query.type == "check") {
            for (const auto &it : elements[query.ind])
                std::cout << it << " ";
            std::cout << "\n";
        } else {
            auto &bucket = elements[hash_func(query.s)];
            auto it = std::find(begin(bucket), end(bucket), query.s);
            if (query.type == "find")
                writeSearchResult(it != end(bucket));
            else if (query.type == "add") {
                if (it == end(bucket))
                    bucket.push_front(query.s);
            } else if (query.type == "del") {
                if (it != end(bucket))
                    bucket.erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count = 0;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
