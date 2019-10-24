#include "json.h"

#include <iostream>
#include <vector>

using namespace std;

struct Spending {
    string category;
    int amount;
};

vector<Spending> LoadFromJson(istream &input) {
    Document doc = Load(input);
    const vector<Node> &nodes = doc.GetRoot().AsArray();
    vector<Spending> res;
    for (const auto &node : nodes) {
        auto &attrs = node.AsMap();
        res.push_back({
            attrs.at("category").AsString(),
            attrs.at("amount").AsInt()
        });
    }
    return res;
}