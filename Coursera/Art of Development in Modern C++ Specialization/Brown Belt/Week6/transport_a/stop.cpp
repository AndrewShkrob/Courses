#include "stop.h"

using namespace std;

istream &operator>>(istream &is, Stop &stop) {
    while (is.peek() == ' ')
        is.ignore();
    getline(is, stop.name, ':');
    is >> stop.coords.latitude;
    is.ignore(2);
    is >> stop.coords.longitude;
    return is;
}