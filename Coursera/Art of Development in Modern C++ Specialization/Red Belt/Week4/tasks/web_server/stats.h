#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats {
public:

    Stats();

    void AddMethod(string_view method);

    void AddUri(string_view uri);

    [[nodiscard]] const map<string_view, int>& GetMethodStats() const;

    [[nodiscard]] const map<string_view, int>& GetUriStats() const;

private:
    const string_view unknown_method = "UNKNOWN";
    const string_view unknown_uri = "unknown";
    map<string_view, int> method_stats;
    map<string_view, int> uri_stats;
};

HttpRequest ParseRequest(string_view line);