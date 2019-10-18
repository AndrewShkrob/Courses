#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    using value_type = typename RandomIt::value_type;
    if (distance(range_begin, range_end) < 2)
        return;
    vector<value_type> arr(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto beg = arr.begin();
    auto first = beg + arr.size() / 3;
    auto second = first + arr.size() / 3;
    auto end = arr.end();
    vector<value_type> tmp;
    MergeSort(beg, first);
    MergeSort(first, second);
    MergeSort(second, end);
    merge(
            make_move_iterator(beg),
            make_move_iterator(first),
            make_move_iterator(first),
            make_move_iterator(second),
            back_inserter(tmp)
    );
    merge(
            make_move_iterator(tmp.begin()),
            make_move_iterator(tmp.end()),
            make_move_iterator(second),
            make_move_iterator(end),
            range_begin
    );
}