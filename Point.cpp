//
// Created by zivben on 8/28/16.
//

#include "Point.h"

Point::Point() {
    _xCord = NULL;
    _yCord = NULL;

}

Point::Point(int x, int y) {
    set(x,y);
}

Point::Point(const Point &oPnt){
    set(oPnt._xCord,oPnt._yCord);
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

bool Point::operator==(const Point &oPnt) {
    return this->_stringRep.compare(oPnt._stringRep) == 0;
}
