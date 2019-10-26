#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <set>
#include <map>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Person {
    string name;
    int age, income;
    char gender;
};

istream &operator>>(istream &is, Person &person) {
    is >> person.name >> person.age >> person.income >> person.gender;
    return is;
}

class PersonStats {
private:
    template<class NameContainer, class PopularName>
    void UpdatePopularName(NameContainer &container, PopularName &popularName, const Person &person) {
        size_t count = ++container[person.name];

        if (!popularName.has_value() || (popularName->first != person.name && popularName->second < count))
            popularName.emplace(person.name, count);
        else if (popularName->first != person.name && popularName->second == count) {
            popularName->first = min(popularName->first, person.name);
            popularName->second = container[popularName->first];
        } else if (popularName->first == person.name)
            popularName->second++;
    }

public:
    void Add(const Person &person) {
        count_for_age[person.age]++;
        if (person.gender == 'M') {
            UpdatePopularName(men_names, popular_m_name, person);
        } else
            UpdatePopularName(women_names, popular_w_name, person);
        person_incomes.push_back(static_cast<size_t>(person.income));
    }

    string CountWithAge(size_t age) const {
        auto it = count_for_age.lower_bound(age);
        size_t amt = 0;
        for (; it != end(count_for_age); ++it)
            amt += it->second;
        return "There are " + to_string(amt) + " adult people for maturity age " + to_string(age);
    }

    string MaxTotalIncome(size_t count) {
        if (!sorted) {
            sort(rbegin(person_incomes), rend(person_incomes));
            sorted = true;
            for (size_t i = 0; i < person_incomes.size(); ++i) {
                if (i == 0) {
                    top_wealthy_persons.push_back(person_incomes[i]);
                } else
                    top_wealthy_persons.push_back(top_wealthy_persons[i - 1] + person_incomes[i]);
            }
        }
        return "Top-" + to_string(count) + " people have total income " + to_string(top_wealthy_persons[count - 1]);
    }

    string PopularName(char gender) const {
        const optional<pair<string, size_t>> &popular = [&] {
            return gender == 'M' ? popular_m_name : popular_w_name;
        }();
        if (!popular.has_value()) {
            ostringstream os;
            os << "No people of gender " << gender;
            return os.str();
        }
        ostringstream os;
        os << "Most popular name among people of gender " << gender << " is " << popular->first;
        return os.str();
    }

private:
    map<size_t, size_t> count_for_age;
    unordered_map<string, size_t> men_names;
    unordered_map<string, size_t> women_names;
    vector<size_t> person_incomes;
    bool sorted = false;
    vector<size_t> top_wealthy_persons;
    optional<pair<string, size_t>> popular_m_name;
    optional<pair<string, size_t>> popular_w_name;
};

vector<Person> ReadPeople(istream &input, PersonStats &stats) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person &p : result) {
        input >> p;
        stats.Add(p);
    }

    return result;
}

int main() {
    PersonStats stats;
    vector<Person> people = ReadPeople(cin, stats);

    for (string command; cin >> command;) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;
            cout << stats.CountWithAge(adult_age) << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;
            cout << stats.MaxTotalIncome(count) << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;
            cout << stats.PopularName(gender) << '\n';
        }
    }
}