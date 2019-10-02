#include <bits/stdc++.h>

using namespace std;

struct Specialization {
    string spec;

    explicit Specialization(string new_spec) : spec(move(new_spec)) {}
};

struct Course {
    string course;

    explicit Course(string new_course) : course(move(new_course)) {}
};

struct Week {
    string week;

    explicit Week(string new_week) : week(move(new_week)) {}
};

struct LectureTitle {
    string specialization;
    string course;
    string week;

    LectureTitle(Specialization specialization, Course course, Week week) {
        this->specialization = specialization.spec;
        this->course = course.course;
        this->week = week.week;
    }
};