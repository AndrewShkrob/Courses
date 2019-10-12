#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

class ReadingManager {
public:
    ReadingManager() {}

    void Read(int user_id, int page_count) {
        if (auto it(user_to_page.find(user_id)); it != user_to_page.end()) {
            page_to_users[it->second].erase(user_id);
        }
        page_to_users[page_count].insert(user_id);
        user_to_page[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if (user_to_page.find(user_id) == user_to_page.end()) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        const int page_count = user_to_page.at(user_id);
        auto page_pos = page_to_users.find(page_count);
        int position = 0;
        while (page_pos != page_to_users.end()) {
            position += page_pos->second.size();
            ++page_pos;
        }
        if (position == user_count) {
            return 0;
        }
        return (user_count - position) * 1.0 / (user_count - 1);
    }

private:
    map<int, set<int>> page_to_users;
    unordered_map<int, int> user_to_page;

    int GetUserCount() const {
        return user_to_page.size();
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}