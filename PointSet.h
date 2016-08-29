//
// Created by zivben on 8/28/16.
//

#ifndef EX1_POINTSET_H
#define EX1_POINTSET_H
#define NOT_FOUND -1

#include <string>
#include "Point.h"

class PointSet {
private:

    int static const _initialCapacity = 8;
    int _currentCapacity = 0;
    int _currentOccupancy = 0;
    Point *_pointArray;

    void increaseCapacity();
    void decreaseCapacity();

    int contains(const Point &pPoint)const;
    bool compHelper(const PointSet &oPntSt);

public:
    PointSet();
    PointSet(int size);
    PointSet(const PointSet* PntSt);
    ~PointSet();
    std::string toString();
    bool add(Point pnt);
    bool add(int x, int y);
    bool remove(const Point &pnt);

    int size()const;
    bool operator==(const PointSet& oPntSt);
    bool operator!=(const PointSet& oPntSt);
    PointSet * operator-(const PointSet& oPntSt);

    PointSet * operator&(const PointSet& oPntSt);
};


#endif //EX1_POINTSET_H

