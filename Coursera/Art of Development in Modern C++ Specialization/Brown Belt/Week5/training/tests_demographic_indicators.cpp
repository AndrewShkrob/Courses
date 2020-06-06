#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void TestReadPersons() {
    istringstream is("1 31 1 0");
    auto persons = ReadPersons(is);
    ASSERT_EQUAL(persons.size(), 1);
    ASSERT_EQUAL(persons[0].age, 31);
    ASSERT_EQUAL(static_cast<int>(persons[0].gender), static_cast<int>(Gender::MALE));
    ASSERT_EQUAL(persons[0].is_employed, 0);
}

void TestOperatorEq() {
    Person p1{1, Gender::MALE, true};
    Person p2 = p1;
    ASSERT(p1 == p2);
    p2.age = 2;
    ASSERT(!(p1 == p2));
    p2 = p1;
    p2.gender = Gender::FEMALE;
    ASSERT(!(p1 == p2));
    p2 = p1;
    p2.is_employed = false;
    ASSERT(!(p1 == p2));
}

void TestPrintPerson() {
    Person p1{1, Gender::MALE, true};
    ostringstream os;
    os << p1;
    ASSERT_EQUAL(os.str(), "Person(age=1, gender=1, is_employed=true)");
}

void TestPrintStats() {
    AgeStats stats{0, 0, 0, 0, 0, 0};
    ostringstream os;
    PrintStats(stats, os);
    ASSERT_EQUAL(os.str(), R"(Median age = 0
Median age for females = 0
Median age for males = 0
Median age for employed females = 0
Median age for unemployed females = 0
Median age for employed males = 0
Median age for unemployed males = 0
)");
}

bool operator==(const AgeStats &st1, const AgeStats &st2) {
    return make_tuple(st1.total, st1.females, st1.males, st1.employed_females, st1.unemployed_females,
                      st1.employed_males, st1.unemployed_males) ==
           make_tuple(st2.total, st2.females, st2.males, st2.employed_females, st2.unemployed_females,
                      st2.employed_males, st2.unemployed_males);
}

void TestComputeStats() {
    {
        AgeStats empty{0, 0, 0, 0, 0, 0, 0};
        ASSERT_EQUAL(ComputeStats({}), empty);
    }
    {
        AgeStats male{1, 0, 1, 0, 0, 1, 0};
        vector<Person> p{{1, Gender::MALE, true}};
        ASSERT_EQUAL(ComputeStats(p), male);
    }
    {
        AgeStats female{1, 1, 0, 0, 1, 0, 0};
        vector<Person> p{{1, Gender::FEMALE, false}};
        ASSERT_EQUAL(ComputeStats(p), female);
    }
    {
        AgeStats stats{1, 1, 1, 1, 0, 0, 1};
        vector<Person> p{{1, Gender::FEMALE, true}, {1, Gender::MALE, false}};
        ASSERT_EQUAL(ComputeStats(p), stats);
    }
    {
        vector<Person> persons = {
                {31, Gender::MALE, false},
                {40, Gender::FEMALE, true},
                {24, Gender::MALE, true},
                {20, Gender::FEMALE, true},
                {80, Gender::FEMALE, false},
                {78, Gender::MALE, false},
                {10, Gender::FEMALE, false},
                {55, Gender::MALE, true},
        };
        AgeStats stats{40, 40, 55, 40, 80, 55, 78};
        ASSERT_EQUAL(ComputeStats(persons), stats);
    }
}

void RunTests() {
    TestRunner tr;
    RUN_TEST(tr, TestReadPersons);
    RUN_TEST(tr, TestOperatorEq);
    RUN_TEST(tr, TestPrintPerson);
    RUN_TEST(tr, TestPrintStats);
    RUN_TEST(tr, TestComputeStats);
}

int main() {
    RunTests();
    PrintStats(ComputeStats(ReadPersons()));
    return 0;
}