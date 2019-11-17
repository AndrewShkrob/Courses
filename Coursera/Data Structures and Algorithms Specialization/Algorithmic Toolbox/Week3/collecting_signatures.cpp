#include <bits/stdc++.h>

using namespace std;

struct Segment {
    int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    sort(begin(segments), end(segments), [](const Segment &a, const Segment &b) { return a.end < b.end; });
    size_t idx = 0;
    while (idx < segments.size()) {
        points.push_back(segments[idx].end);
        while (idx < segments.size() && segments[idx].start <= points.back())
            idx++;
    }
    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
} 