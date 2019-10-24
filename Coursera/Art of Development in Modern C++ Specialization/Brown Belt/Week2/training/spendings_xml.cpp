#include "xml.h"

#include <iostream>
#include <vector>

using namespace std;

struct Spending {
    string category;
    int amount;
};

vector<Spending> LoadFromXml(istream &input) {
    Document doc = Load(input);
    auto nodes = doc.GetRoot().Children();
    vector<Spending> res;
    for (auto &node : nodes) {
        res.push_back({
                              node.AttributeValue<string>("category"),
                              node.AttributeValue<int>("amount")
                      });
    }
    return res;
}
