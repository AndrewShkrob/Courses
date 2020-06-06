#include <string>
#include <sstream>
#include "coordinates.h"
#include "parse.h"

#ifndef BROWN_BELT_STOP_H
#define BROWN_BELT_STOP_H

struct Stop {
    std::string name;
    Coords coords;
};

std::istream &operator>>(std::istream &is, Stop &stop);

#endif //BROWN_BELT_STOP_H
