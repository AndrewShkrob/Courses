#pragma once

#include <string>
#include <string_view>
#include <deque>
#include <map>
#include <vector>
#include <istream>

class InvertedIndex {
public:
    struct Entry {
        size_t doc_id;
        size_t rating;
    };

    InvertedIndex() = default;

    explicit InvertedIndex(std::istream &is);

    void Add(std::string document);

    const std::vector<Entry> &Lookup(const std::string_view &word) const;

    const std::deque<std::string> &GetDocuments() const;

private:
    std::map<std::string_view, std::vector<Entry>> index;
    std::deque<std::string> document_pool;
};
