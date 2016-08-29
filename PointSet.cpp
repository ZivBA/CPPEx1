//
// Created by zivben on 8/28/16.
//

#include "PointSet.h"

PointSet::PointSet() {
     Point pointArray[_initialCapacity];
    _currentCapacity = _initialCapacity;
}

PointSet::PointSet(int size) {
    Point pointArray[size];
    _currentCapacity = size;

}

PointSet::PointSet(const PointSet *PntSt) {
    _currentCapacity = PntSt->size();
    for (int i=0; i<= PntSt->size(); i++){
        add(PntSt->pointArray[i]);
    }

}

PointSet::~PointSet() {
    delete pointArray;
}

std::string PointSet::toString() {
    return nullptr;
}

bool PointSet::add(int x, int y) {
    Point newPnt = Point(x,y);
    return this->add(newPnt);

}

bool PointSet::add(const Point &pnt) {
    if (!contains(pnt)==-1){
        return false;
    }
    if (_currentCapacity - _currentOccupancy <=2 ){
        increaseCapacity();
    }
    pointArray[_currentOccupancy++] = Point(pnt);
    return true;
}

bool PointSet::remove(const Point &pnt) {
    int res = contains(pnt);
    if (res == -1) return false;
    delete &pointArray[res];
    pointArray[res] = pointArray[--_currentOccupancy];
    if (_currentOccupancy <= _currentCapacity/2) decreaseCapacity();
    return true;


}

int PointSet::size()const {
    return _currentOccupancy;
}

int PointSet::contains(const Point &pPoint)const {
    for (int i=0; i<= _currentCapacity; i++){
        if (pointArray[i] == pPoint){
            return i;
        }
    }
    return -1;
}

void PointSet::increaseCapacity() {

    Point* newArray = new Point[_currentCapacity*2];
    for (int i=0; i<=_currentOccupancy; i++){
        newArray[i] = pointArray[i];
    }
    _currentCapacity = _currentCapacity*2;
}

void PointSet::decreaseCapacity() {
    Point* newArray = new Point[_currentCapacity/2];
    for (int i=0; i<=_currentOccupancy; i++){
        newArray[i] = pointArray[i];
    }
    _currentCapacity = _currentCapacity/2;

}
bool PointSet::compHelper(const PointSet &oPntSt){
    if (this->size()!=oPntSt.size()){
        return false;
    }
    for (int i=0; i<=this->size(); i++){
        if (!oPntSt.contains(pointArray[i])){
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
        if (!oPntSt.contains(pointArray[i])){
            newSet->add(pointArray[i]);
        }
    }
    return newSet;
}

PointSet *PointSet::operator&(const PointSet &oPntSt) {
    return nullptr;
}
