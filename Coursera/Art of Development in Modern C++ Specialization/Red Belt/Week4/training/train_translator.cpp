#include <bits/stdc++.h>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        const string_view source_view = GetCopied(source);
        const string_view target_view = GetCopied(target);
        forward_dict[source_view] = target_view;
        backward_dict[target_view] = source_view;
    }

    string_view TranslateForward(string_view source) const {
        return Translate(forward_dict, source);
    }

    string_view TranslateBackward(string_view target) const {
        return Translate(backward_dict, target);
    }

private:
    map<string_view, string_view> forward_dict;
    map<string_view, string_view> backward_dict;
    deque<string> dict;

    string_view GetCopied(string_view sv) {
        for (const auto *map_ptr : {&forward_dict, &backward_dict}) {
            const auto it = map_ptr->find(sv);
            if (it != map_ptr->end()) {
                return it->first;
            }
        }
        return dict.emplace_back(sv);
    }

    static string_view Translate(const map<string_view, string_view> &dict, string_view s) {
        if (const auto it = dict.find(s); it != dict.end()) {
            return it->second;
        } else {
            return {};
        }
    }
};