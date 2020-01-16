#include <bits/stdc++.h>

using namespace std;

bool is_opening_bracket(char bracket) {
    return bracket == '(' || bracket == '[' || bracket == '{';
}

bool is_closing_bracket(char bracket) {
    return bracket == ')' || bracket == ']' || bracket == '}';
}

char get_opening_bracket(char bracket) {
    if (bracket == ')')
        return '(';
    else if (bracket == ']')
        return '[';
    else if (bracket == '}')
        return '{';
    else
        return bracket;
}

int get_first_unmatched_closing_bracket(const string &text) {
    stack<int> st;
    for (int i = 0; i < text.size(); ++i) {
        if (is_closing_bracket(text[i])) {
            char opening = get_opening_bracket(text[i]);
            if (st.empty())
                return i;
            while (!st.empty()) {
                int top = st.top();
                st.pop();
                if (is_opening_bracket(text[top]) && text[top] != opening)
                    return i;
                else if (text[top] == opening) {
                    break;
                }
            }
        } else if (is_opening_bracket(text[i]))
            st.push(i);
    }
    if (!st.empty())
        return st.top();
    return -1;
}

int main() {
    string text;
    cin >> text;
    int idx = get_first_unmatched_closing_bracket(text);
    if (idx == -1)
        cout << "Success";
    else
        cout << idx + 1;
}