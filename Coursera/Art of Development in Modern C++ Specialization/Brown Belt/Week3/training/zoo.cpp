#include "animals.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

using namespace std;

using Zoo = vector<unique_ptr<Animal>>;

Zoo CreateZoo(istream &in) {
    Zoo zoo;
    string word;
    while (in >> word) {
        if (word == "Tiger") {
            zoo.emplace_back(new Tiger);
        } else if (word == "Wolf") {
            zoo.emplace_back(new Wolf);
        } else if (word == "Fox") {
            zoo.emplace_back(new Fox);
        } else {
            throw runtime_error("Unknown animal!");
        }
    }
    return zoo;
}

void Process(const Zoo &zoo, ostream &out) {
    for (const auto &animal : zoo) {
        out << animal->Voice() << "\n";
    }
}