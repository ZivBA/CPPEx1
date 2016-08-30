//
// Created by zivben on 8/28/16.
//

#include <sstream>
#include "PointSet.h"

PointSet::PointSet()  : PointSet(_initialCapacity){

}

PointSet::PointSet(int const size) {
     _pointArray = new Point*[size];
    _currentCapacity = size;
    std::fill_n(_pointArray,_currentCapacity, nullptr);
}

PointSet::PointSet(const PointSet *PntSt) : PointSet(PntSt->size()) {
    for (int i=0; i< PntSt->size(); i++){
        add(new Point(*PntSt->_pointArray[i]));
    }
}

PointSet::~PointSet() {
    for (int i=0; i<_currentCapacity; i++){
        delete _pointArray[i];
    }
    delete _pointArray;
}

std::string PointSet::toString() {
    std::stringstream ss;
    for (int i=0; i<=this->_currentOccupancy; i++){

        ss << _pointArray[i]->toString();
        if (i != _currentOccupancy-1){
            ss << ",";
        }
    }
    return ss.str();
}

bool PointSet::add(int x, int y) {
    Point* newPnt = new Point(x, y);
    return this->add(newPnt);

}

bool PointSet::add(Point *pnt) {
    if (contains(*pnt)!=NOT_FOUND){
        return false;
    }
    if (_currentCapacity - _currentOccupancy <=1 ){
        increaseCapacity();
    }
    _pointArray[_currentOccupancy++] = pnt;
    return true;
}

bool PointSet::remove(const Point *pnt) {
    int res = contains(*pnt);
    if (res == NOT_FOUND) return false;
    delete &_pointArray[res];
    _pointArray[res] = _pointArray[_currentOccupancy-2];
    _pointArray[--_currentOccupancy] = _pointArray[_currentOccupancy+1];
    if (_currentOccupancy <= _currentCapacity/2) decreaseCapacity();
    return true;


}

int PointSet::size()const {
    return _currentOccupancy;
}

int PointSet::contains(Point pPoint)const {
    for (int i=0; i<= _currentOccupancy; i++){
        if (_pointArray[i] == nullptr) {
            continue;
        }
        else if (*_pointArray[i] == pPoint){
            return i;
        }
    }
    return NOT_FOUND;
}

void PointSet::increaseCapacity() {
    _currentCapacity = _currentCapacity*2;

    Point** newArray = new Point*[_currentCapacity];
    std::swap_ranges(_pointArray[0], _pointArray[_currentOccupancy],newArray[0]);

    delete[] _pointArray;
    _pointArray = newArray;

}

void PointSet::decreaseCapacity() {
    _currentCapacity = _currentCapacity/2;
    Point** newArray = new Point*[_currentCapacity];
    std::fill_n(newArray,_currentCapacity, nullptr);
    std::swap_ranges(_pointArray[0], _pointArray[_currentOccupancy],newArray[0]);

    delete[] _pointArray;
    _pointArray = newArray;


}
bool PointSet::operator==(const PointSet &oPntSt) const{
    if (this->size()!=oPntSt.size()){
        return false;
    }
    for (int i=0; i<=this->size(); i++){
        if (!oPntSt.contains(*_pointArray[i])){
            return false;
        }
    }
    return true;
}

bool PointSet::operator!=(const PointSet &oPntSt) const{
    return !operator==(oPntSt);
}

PointSet PointSet::operator-(const PointSet &oPntSt) const {
    PointSet newSet = PointSet(this->size());
    for (int i=0; i<= _currentOccupancy; i++){

        if (oPntSt.contains(*_pointArray[i]) == NOT_FOUND){
            newSet.add(_pointArray[i]);
        }
    }
    return newSet;
}

PointSet PointSet::operator&(const PointSet oPntSt) const {
    return PointSet();
}
