#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector<pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void GenerateSwaps() {
        swaps_.clear();
        for (int i = data_.size() / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
    }

    void SiftDown(int idx) {
        int max_index = idx;
        int left_child = 2 * idx + 1;
        if (left_child < data_.size() && data_[left_child] < data_[max_index])
            max_index = left_child;
        int right_child = 2 * idx + 2;
        if (right_child < data_.size() && data_[right_child] < data_[max_index])
            max_index = right_child;
        if (idx != max_index) {
            swaps_.emplace_back(idx, max_index);
            swap(data_[idx], data_[max_index]);
            SiftDown(max_index);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
