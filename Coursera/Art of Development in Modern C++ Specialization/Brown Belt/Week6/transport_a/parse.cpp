#include <cctype>
#include "parse.h"

using namespace std;

string_view Strip(string_view s) {
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && isspace(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

std::string_view LeftStrip(std::string_view s) {
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
    return s;
}

vector<string_view> SplitBy(string_view s, char sep) {
    vector<string_view> result;
    while (!s.empty()) {
        size_t pos = s.find(sep);
        result.push_back(s.substr(0, pos));
        s.remove_prefix(pos != std::string_view::npos ? pos + 1 : s.size());
    }
    return result;
}