#include <bits/stdc++.h>

using namespace std;

template<typename Predicate>
void run_lambda(const vector<Person> &src, string &&message, Predicate pred) {
    [&]() {
        vector<Person> dst;
        copy_if(
                src.begin(),
                src.end(),
                back_inserter(dst),
                pred
        );
        cout << message << " " << ComputeMedianAge(dst.begin(), dst.end()) << endl;
    }();
}

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    run_lambda(persons, "Median age for females =", [](const Person &p) {
        return p.gender == Gender::FEMALE;
    });
    run_lambda(persons, "Median age for males =", [](const Person &p) {
        return p.gender == Gender::MALE;
    });
    run_lambda(persons, "Median age for employed females =", [](const Person &p) {
        return p.gender == Gender::FEMALE && p.is_employed;
    });
    run_lambda(persons, "Median age for unemployed females =", [](const Person &p) {
        return p.gender == Gender::FEMALE && !p.is_employed;
    });
    run_lambda(persons, "Median age for employed males =", [](const Person &p) {
        return p.gender == Gender::MALE && p.is_employed;
    });
    run_lambda(persons, "Median age for unemployed males =", [](const Person &p) {
        return p.gender == Gender::MALE && !p.is_employed;
    });
}