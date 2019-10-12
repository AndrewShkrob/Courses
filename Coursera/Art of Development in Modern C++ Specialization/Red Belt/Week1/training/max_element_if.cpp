#include <bits/stdc++.h>

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
        ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    ForwardIterator max_element = last;
    bool result_exists = false;
    while (first != last) {
        if (!result_exists && pred(*first)) {
            max_element = first;
            result_exists = true;
        }
        if (pred(*first) && *max_element < *first)
            max_element = first;
        ++first;
    }
    return max_element;
}
