#include <bits/stdc++.h>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (distance(range_begin, range_end) < 3)
        return;
    using value_type = typename RandomIt::value_type;
    vector<value_type> elements(range_begin, range_end);
    size_t third_part = elements.size() / 3;
    auto left_middle = elements.begin() + third_part;
    auto right_middle = left_middle + third_part;
    MergeSort(elements.begin(), left_middle);
    MergeSort(left_middle, right_middle);
    MergeSort(right_middle, elements.end());
    vector<value_type> tmp;
    merge(elements.begin(), left_middle, left_middle, right_middle, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), right_middle, elements.end(), range_begin);
}