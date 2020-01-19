#include <bits/stdc++.h>

using namespace std;

static constexpr size_t multiplier = 1;
static constexpr size_t prime = 50'000'000'007;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int> &output) {
    for (int i : output)
        std::cout << i << " ";
    std::cout << "\n";
}

size_t polyHash(const string &str, int beg = 0, int end = -1) {
    if (end == -1)
        end = str.size();
    size_t hash = 0;
    for (int i = end - 1; i >= beg; --i)
        hash = (hash * multiplier + str[i]) % prime;
    return hash;
}

std::vector<int> precomputeHashes(const string &text, const int pattern_size) {
    std::vector<int> hashes(text.size() - pattern_size + 1);
    hashes.back() = polyHash(text, text.size() - pattern_size);
    size_t y = 1;
    for (int i = 1; i <= pattern_size; ++i)
        y = (y * multiplier) % prime;
    for (int i = text.size() - pattern_size - 1; i >= 0; --i) {
        hashes[i] = (hashes[i + 1] * multiplier + text[i] - y * text[i + pattern_size]) % prime;
    }
    return hashes;
}

std::vector<int> get_occurrences(const Data &input) {
    const string &t = input.text;
    const string &p = input.pattern;
    auto p_hash = polyHash(p);
    auto hashes = precomputeHashes(t, p.size());
    std::vector<int> ans;
    for (size_t i = 0; i + p.size() <= t.size(); ++i) {
        if (hashes[i] != p_hash)
            continue;
        if (t.compare(i, p.size(), p) == 0)
            ans.push_back(i);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
