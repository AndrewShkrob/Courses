#include <bits/stdc++.h>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string> &words) {
        int prev_size = dict.size();
        dict.insert(words.begin(), words.end());
        return dict.size() - prev_size;
    }

    vector<string> KnownWords() {
        return vector<string>(dict.begin(), dict.end());
    }
};