#include <bits/stdc++.h>

using namespace std;

struct Student {
    string first_name;
    string last_name;
    int birth_day;
    int birth_month;
    int birth_year;
};

int main() {
    int N;
    cin >> N;
    vector<Student> students;
    for (int i = 0; i < N; i++) {
        string first_name;
        string last_name;
        int birth_day;
        int birth_month;
        int birth_year;
        cin >> first_name >> last_name >> birth_day >> birth_month >> birth_year;
        students.push_back({first_name, last_name, birth_day, birth_month, birth_year});
    }
    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        string query;
        int st_num;
        cin >> query;
        if (query != "name" && query != "date") {
            string tmp;
            getline(cin, tmp);
            cout << "bad request" << endl;
            continue;
        } else
            cin >> st_num;
        st_num--;
        if (st_num < 0 || st_num >= students.size()) {
            cout << "bad request" << endl;
            continue;
        }
        if (query == "name")
            cout << students[st_num].first_name << " " << students[st_num].last_name << endl;
        else if (query == "date")
            cout << students[st_num].birth_day << "." << students[st_num].birth_month << "."
                 << students[st_num].birth_year << endl;
    }
}