//
// Created by zivben on 8/28/16.
//

#include "PointSet.h"

PointSet::PointSet() {
    _pointStack = new Stack();

}

PointSet::~PointSet() {

}

std::string PointSet::toString() {
    return nullptr;
}

bool PointSet::add(const Point &pnt) {
    return false;
}

bool PointSet::remove(const Point &pnt) {
    return false;
}

int PointSet::size() {
    return 0;
}

PointSet::Stack::Stack(int capacity) {

    if (capacity <= 0)
        throw std::string("Stack's _capacity must be positive");
    _storage = new int[capacity];
    this->_capacity = capacity;
    _top = -1;

}

void PointSet::Stack::push(int value) {
    if (_top == _capacity) {
        _top++;
        _storage[_top] = value;
    }
}

int PointSet::Stack::peek() {
    if (_top == -1)
        throw std::string("Stack is empty");
    return _storage[_top];

}

void PointSet::Stack::pop() {
    if (_top == -1)
        throw std::string("Stack is empty");
    _top--;

}

bool PointSet::Stack::isEmpty() {
    return (_top == -1);
}

PointSet::Stack::~Stack() {
    delete[] _storage;
}

PointSet::Stack::Stack() {
    PointSet::Stack::Stack(_defautlStackSize);
}
