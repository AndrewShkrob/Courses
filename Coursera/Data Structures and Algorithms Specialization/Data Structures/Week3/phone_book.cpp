#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <bits/unordered_map.h>

using std::string;
using std::vector;
using std::unordered_map;
using std::cin;

struct Query {
    string type, name = "not found";
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string> &result) {
    for (const auto &i : result)
        std::cout << i << "\n";
}

vector<string> process_queries(const vector<Query> &queries) {
    vector<string> result;
    unordered_map<int, string> number_name{};
    unordered_map<string, int> name_number{};
    for (const auto &query : queries)
        if (query.type == "add") {
            number_name[query.number] = query.name;
            name_number[query.name] = query.number;
        } else if (query.type == "del") {
            string name = number_name[query.number];
            number_name.erase(query.number);
            name_number.erase(name);
        } else {
            if (number_name.find(query.number) != end(number_name))
                result.push_back(number_name[query.number]);
            else
                result.emplace_back("not found");
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
