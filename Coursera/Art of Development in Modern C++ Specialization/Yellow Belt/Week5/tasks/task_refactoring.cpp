#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;

class Person {
public:
    Person(const string &name, const string &position) : Name(name), Position(position) {}

    virtual void Walk(const string &destination) {
        Log() << " walks to: " << destination << endl;
    };

    string GetName() const {
        return Name;
    }

    string GetPosition() const {
        return Position;
    }

protected:
    string GetPersonDescriptor() const {
        return Position + ": " + Name;
    }

    ostream &Log() {
        cout << GetPersonDescriptor();
        return cout;
    }

    const string Name;
    const string Position;
};

class Student : public Person {
public:
    Student(const string &name, const string &favouriteSong)
            : Person(name, "Student"),
              FavouriteSong(favouriteSong) {}

    void Learn() {
        Log() << " learns" << endl;
    }

    void Walk(const string &destination) override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() {
        Log() << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};

class Teacher : public Person {
public:
    Teacher(const string &name, const string &subject)
            : Person(name, "Teacher"),
              Subject(subject) {}

    void Teach() {
        Log() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};

class Policeman : public Person {
public:
    Policeman(const string &name) : Person(name, "Policeman") {}

    void Check(const Person &person) {
        Log() << " checks " << person.GetPosition() << ". "
              << person.GetPosition() << "'s Name is: " << person.GetName() << endl;
    }
};

void VisitPlaces(Person &person, const vector<string> &places) {
    for (const auto &place : places) {
        person.Walk(place);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
