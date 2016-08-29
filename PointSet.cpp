//
// Created by zivben on 8/28/16.
//

#include <sstream>
#include "PointSet.h"

PointSet::PointSet()  : PointSet(_initialCapacity){

}

PointSet::PointSet(int const size) {

     _pointArray = new Point[size];
    _currentCapacity = size;

}

PointSet::PointSet(const PointSet *PntSt) : PointSet(PntSt->size()) {
    _currentCapacity = PntSt->size();
    for (int i=0; i< PntSt->size(); i++){
        add(PntSt->_pointArray[i]);
    }

}

PointSet::~PointSet() {
    delete _pointArray;
}

std::string PointSet::toString() {
    std::stringstream ss;
    for (int i=0; i<=this->_currentOccupancy; i++){

        ss << _pointArray[i].toString();
        if (i != _currentOccupancy-1){
            ss << ",";
        }
    }
    return ss.str();
}

bool PointSet::add(int x, int y) {
    Point newPnt = Point(x, y);
    return this->add(newPnt);

}

bool PointSet::add(Point pnt) {
    if (contains(pnt)!=NOT_FOUND){
        return false;
    }
    if (_currentCapacity - _currentOccupancy <=1 ){
        increaseCapacity();
    }
    _pointArray[_currentOccupancy++] = Point(pnt);
    return true;
}

bool PointSet::remove(const Point &pnt) {
    int res = contains(pnt);
    if (res == NOT_FOUND) return false;
    delete &_pointArray[res];
    _pointArray[res] = _pointArray[--_currentOccupancy];
    if (_currentOccupancy <= _currentCapacity/2) decreaseCapacity();
    return true;


}

int PointSet::size()const {
    return _currentOccupancy;
}

int PointSet::contains(const Point &pPoint)const {
    for (int i=0; i<= _currentOccupancy; i++){
        if (_pointArray[i] == pPoint){
            return i;
        }
    }
    return NOT_FOUND;
}

void PointSet::increaseCapacity() {

    Point* newArray = new Point[_currentCapacity*2];
    for (int i=0; i<=_currentOccupancy; i++){
        newArray[i] = _pointArray[i];
    }
    _currentCapacity = _currentCapacity*2;
}

void PointSet::decreaseCapacity() {
    Point* newArray = new Point[_currentCapacity/2];
    for (int i=0; i<=_currentOccupancy; i++){
        newArray[i] = _pointArray[i];
    }
    _currentCapacity = _currentCapacity/2;

}
bool PointSet::compHelper(const PointSet &oPntSt){
    if (this->size()!=oPntSt.size()){
        return false;
    }
    for (int i=0; i<=this->size(); i++){
        if (!oPntSt.contains(_pointArray[i])){
            return false;
        }
    }
    return true;
}
bool PointSet::operator==(const PointSet &oPntSt) {
    return compHelper(oPntSt);
}

bool PointSet::operator!=(const PointSet &oPntSt) {
    return !compHelper(oPntSt);
}

PointSet * PointSet::operator-(const PointSet &oPntSt) {
    PointSet *newSet = new PointSet[this->size()];
    for (int i=0; i<= _currentOccupancy; i++){

        if (oPntSt.contains(_pointArray[i]) == NOT_FOUND){
            newSet->add(_pointArray[i]);
        }
    }
    return newSet;
}

PointSet *PointSet::operator&(const PointSet &oPntSt) {
    return nullptr;
}
