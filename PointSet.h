//
// Created by zivben on 8/28/16.
//

#ifndef EX1_POINTSET_H
#define EX1_POINTSET_H


#include <string>
#include "Point.h"

class PointSet {
private:


public:
    PointSet();
    ~PointSet();
    std::string toString();
    bool add(const Point &pnt);
    bool remove(const Point &pnt);
    int size();

};


#endif //EX1_POINTSET_H

