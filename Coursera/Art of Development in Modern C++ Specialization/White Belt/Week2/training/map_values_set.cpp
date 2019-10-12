set<string> BuildMapValuesSet(const map<int, string> &m) {
    set<string> values_set;
    for(auto &&it : m)
        values_set.insert(it.second);
    return values_set;
}
