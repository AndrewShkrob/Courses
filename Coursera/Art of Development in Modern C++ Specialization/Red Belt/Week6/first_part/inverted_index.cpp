#include "inverted_index.h"
#include "split_into_words.h"

using namespace std;

InvertedIndex::InvertedIndex(istream &is) {
    string document;
    while (getline(is, document))
        Add(move(document));
}

void InvertedIndex::Add(string document) {
    document_pool.push_back(move(document));

    const size_t doc_id = document_pool.size() - 1;
    for (string_view word : SplitIntoWords(document_pool.back())) {
        auto &doc_ids = index[word];
        if (!doc_ids.empty() && doc_ids.back().doc_id == doc_id)
            doc_ids.back().rating++;
        else
            doc_ids.push_back({doc_id, 1});
    }
}

const vector<InvertedIndex::Entry> &InvertedIndex::Lookup(const string_view &word) const {
    static vector<InvertedIndex::Entry> empty;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty;
    }
}

const std::deque<std::string> &InvertedIndex::GetDocuments() const {
    return document_pool;
}