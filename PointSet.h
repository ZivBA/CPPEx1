//
// Created by zivben on 8/28/16.
//

#ifndef EX1_POINTSET_H
#define EX1_POINTSET_H


#include <string>
#include "Point.h"

class PointSet
{
private:
	const int notFound = -1;
	const int static _initialCapacity = 8;
	int _currentCapacity = 0;
	int _currentOccupancy = 0;
	Point **_pointArray;

	void increaseCapacity();

	void decreaseCapacity();

	int contains(const Point &pPoint) const;

public:
	PointSet();

	PointSet(int size);

	PointSet(const PointSet &PntSt);

	~PointSet();

	std::string toString();

	bool add(Point const &pnt);

	bool remove(const Point &pnt);

	int size() const;

	bool operator==(const PointSet &oPntSt) const;

	bool operator!=(const PointSet &oPntSt) const;

	PointSet operator-(const PointSet &oPntSt) const;

	PointSet operator&(const PointSet &oPntSt) const;

	int convexSort();
};


#endif //EX1_POINTSET_H
