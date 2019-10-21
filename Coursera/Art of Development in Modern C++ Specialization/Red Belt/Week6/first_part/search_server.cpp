#include "search_server.h"
#include "iterator_range.h"
#include "split_into_words.h"

#include <algorithm>
#include <iostream>
#include <numeric>

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    index = InvertedIndex{document_input};
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
) {
    const auto &document_pool = index.GetDocuments();
    vector<pair<size_t, size_t>> docid_count(document_pool.size());
    for (string current_query; getline(query_input, current_query);) {
        for (size_t i = 0; i < docid_count.size(); ++i) {
            docid_count[i].first = i;
            docid_count[i].second = 0;
        }
        const auto words = SplitIntoWords(current_query);
        for (const auto &word: words) {
            for (const auto &[docid, rating] : index.Lookup(word)) {
                docid_count[docid].second += rating;
            }
        }
        partial_sort(
                docid_count.begin(),
                Head(docid_count, 5).end(),
                docid_count.end(),
                [](auto &lhs, auto &rhs) {
                    int64_t lhs_docid = lhs.first;
                    auto lhs_hit_count = lhs.second;
                    int64_t rhs_docid = rhs.first;
                    auto rhs_hit_count = rhs.second;
                    return make_pair(lhs_hit_count, -lhs_docid) >
                           make_pair(rhs_hit_count, -rhs_docid);
                }
        );
        search_results_output << current_query << ':';
        for (auto &[docid, hitcount] : Head(docid_count, 5)) {
            if (hitcount == 0)
                break;
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';
    }
}