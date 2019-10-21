#include "split_into_words.h"

using namespace std;

void LeftStrip(string_view &sv) {
    while (!sv.empty() && isspace(sv[0])) {
        sv.remove_prefix(1);
    }
}

string_view ReadToken(string_view &sv) {
    LeftStrip(sv);
    auto pos = sv.find(' ');
    auto word = sv.substr(0, pos);
    sv.remove_prefix(pos != string_view::npos ? pos : sv.size());
    return word;
}

vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> value;
    for (string_view word = ReadToken(line); !word.empty(); word = ReadToken(line)) {
        value.push_back(word);
    }
    return value;
}