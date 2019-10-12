#include <iostream>
#include "stats.h"

using namespace std;

Stats::Stats() {
    method_stats.emplace("GET", 0);
    method_stats.emplace("POST", 0);
    method_stats.emplace("PUT", 0);
    method_stats.emplace("DELETE", 0);
    method_stats.emplace(unknown_method, 0);
    uri_stats.emplace("/", 0);
    uri_stats.emplace("/order", 0);
    uri_stats.emplace("/product", 0);
    uri_stats.emplace("/basket", 0);
    uri_stats.emplace("/help", 0);
    uri_stats.emplace(unknown_uri, 0);
}

void Stats::AddMethod(string_view method) {
    if (method_stats.find(method) == method_stats.end())
        ++method_stats[unknown_method];
    else
        ++method_stats[method];
}

void Stats::AddUri(string_view uri) {
    if (uri_stats.find(uri) == uri_stats.end())
        ++uri_stats[unknown_uri];
    else
        ++uri_stats[uri];
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return uri_stats;
}

HttpRequest ParseRequest(string_view line) {
    string_view method = line;
    method.remove_prefix(method.find_first_not_of(' '));
    method.remove_suffix(method.size() - method.find(' '));
    string_view uri = line;
    uri.remove_prefix(uri.find(method) + method.size() + 1);
    uri.remove_suffix(uri.size() - uri.find(' '));
    string_view protocol = line;
    protocol.remove_prefix(protocol.find(uri) + uri.size() + 1);
    return {method, uri, protocol};
}