//
// Created by zivben on 8/28/16.
//

#include "Point.h"

Point::Point() {
    _xCord = nullptr;
    _yCord = nullptr;

}

Point::Point(int x, int y) {
    set(x,y);
    _stringRep = "null,null";
}

void Point::set(int x, int y) {
    _xCord = x;
    _yCord = y;
    _stringRep = std::to_string(_xCord)+","+std::to_string(_yCord);
}

Point::~Point() {

}

std::string Point::toString() {

    return _stringRep;
}
