#include <bits/stdc++.h>

using namespace std;

class Date {
public:

    Date(int d = 1, int m = 1, int y = 1) {
        if (m < 1 || m > 12)
            throw invalid_argument("Month value is invalid: " + to_string(m));
        if (d < 1 || d > 31)
            throw invalid_argument("Day value is invalid: " + to_string(d));
        day = d;
        month = m;
        year = y;
    }

    int GetYear() const {
        return year;
    }

    int GetMonth() const {
        return month;
    }

    int GetDay() const {
        return day;
    }

    bool operator<(const Date &rhs) const {
        if (year != rhs.year)
            return year < rhs.year;
        if (month != rhs.month)
            return month < rhs.month;
        if (day != rhs.day)
            return day < rhs.day;
        return false;
    }

private:
    int day;
    int month;
    int year;
};

void check_and_ignore(istream &stream, const string &str) {
    if (stream.peek() != '-')
        throw invalid_argument("Wrong date format: " + str);
    stream.ignore(1);
}

istream &operator>>(istream &stream, Date &date) {
    int day;
    int month;
    int year;
    string str_date;
    stream >> str_date;
    stringstream ss(str_date);
    if ((ss.peek() < '0' || ss.peek() > '9') && ss.peek() != '-')
        throw invalid_argument("Wrong date format: " + str_date);
    ss >> year;
    check_and_ignore(ss, str_date);
    if (ss.peek() == -1)
        throw invalid_argument("Wrong date format: " + str_date);
    ss >> month;
    check_and_ignore(ss, str_date);
    if (ss.peek() == -1)
        throw invalid_argument("Wrong date format: " + str_date);
    ss >> day;
    if (!ss.eof())
        throw invalid_argument("Wrong date format: " + str_date);
    date = Date(day, month, year);
    return stream;
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
           << setw(2) << setfill('0') << date.GetMonth() << '-'
           << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

class Database {
public:
    void AddEvent(const Date &date, const string &event) {
        data[date].insert(event);
    }

    bool DeleteEvent(const Date &date, const string &event) {
        if (data.find(date) == data.end())
            return false;
        if (data[date].find(event) == data[date].end())
            return false;
        data[date].erase(event);
        return true;
    }

    int DeleteDate(const Date &date) {
        int amt = data[date].size();
        data.erase(date);
        return amt;
    }

    vector<string> Find(const Date &date) const {
        if (data.find(date) == data.end())
            return {};
        return vector<string>(data.at(date).begin(), data.at(date).end());
    }

    void Print() const {
        for (const auto &[date, strs] : data) {
            for (const auto &str : strs) {
                cout << date << " " << str << endl;
            }
        }
    }

private:
    map<Date, set<string>> data;
};

int main() {
    Database db;
    string str_command;
    try {
        while (getline(cin, str_command)) {
            stringstream ss(str_command);
            string command;
            Date date;
            string event;
            ss >> command;
            if (command == "Add") {
                ss >> date >> event;
                if (event.empty())
                    continue;
                db.AddEvent(date, event);
            } else if (command == "Del") {
                ss >> date;
                if (ss)
                    ss >> event;
                if (event.empty()) {
                    cout << "Deleted " << to_string(db.DeleteDate(date)) << " events" << endl;
                } else {
                    if (db.DeleteEvent(date, event))
                        cout << "Deleted successfully" << endl;
                    else
                        cout << "Event not found" << endl;
                }
            } else if (command == "Find") {
                ss >> date;
                auto events = db.Find(date);
                for (auto &it : events) {
                    cout << it << endl;
                }
            } else if (command == "Print") {
                db.Print();
            } else if (command.empty()) {
                continue;
            } else {
                throw invalid_argument("Unknown command: " + command);
            }

        }
    } catch (exception &ex) {
        cout << ex.what() << endl;
    }

    return 0;
}