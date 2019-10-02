#include <bits/stdc++.h>

using namespace std;

int main() {
    const vector<int> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int current_month = 0;
    vector<vector<string>> tasks_in_days(days_in_months[current_month]);
    int Q;
    cin >> Q;
    while (Q--) {
        string str;
        cin >> str;
        if (str == "ADD") {
            int day;
            string task;
            cin >> day >> task;
            tasks_in_days[day - 1].push_back(task);
        } else if (str == "NEXT") {
            current_month++;
            current_month %= 12;
            if (days_in_months[current_month] < tasks_in_days.size()) {
                int new_last_day = days_in_months[current_month] - 1;
                for (int other_day = new_last_day + 1; other_day < tasks_in_days.size(); other_day++) {
                    tasks_in_days[new_last_day].insert(tasks_in_days[new_last_day].end(),
                                                       tasks_in_days[other_day].begin(),
                                                       tasks_in_days[other_day].end());
                }
            }
            tasks_in_days.resize(days_in_months[current_month]);
        } else if (str == "DUMP") {
            int day;
            cin >> day;
            cout << tasks_in_days[day - 1].size() << " ";
            for (auto &it : tasks_in_days[day - 1])
                cout << it << " ";
            cout << endl;
        }
    }
}