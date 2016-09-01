//
// Created by zivben on 8/28/16.
//

#include <sstream>
#include "PointSet.h"

PointSet::PointSet() : PointSet(_initialCapacity)
{

}

PointSet::PointSet(int const size)
{
	_pointArray = new Point *[size];
	_currentCapacity = size;
	for (int i = 0; i < _currentCapacity; i++)
	{
		_pointArray[i] = new Point();
	}
}

PointSet::PointSet(const PointSet &PntSt) : PointSet(PntSt.size())
{
	for (int i = 0; i < PntSt.size(); i++)
	{
		_pointArray[i] = PntSt._pointArray[i];
	}
}

PointSet::~PointSet()
{
	for (int i = 0; i < _currentCapacity; i++)
	{
		delete _pointArray[i];
	}
	delete _pointArray;
}

std::string PointSet::toString()
{
	std::stringstream ss;
	for (int i = 0; i < this->_currentOccupancy; i++)
	{

		ss << _pointArray[i]->toString();
		if (i != _currentOccupancy - 1)
		{
			ss << "\n";
		}
	}
	return ss.str();
}

//bool PointSet::add(int x, int y) {
//    Point* pnt = new Point(x, y);
//    add(pnt);
//
//}

bool PointSet::add(Point const &pnt)
{
	if (contains(pnt) != notFound)
	{
		return false;
	}
	if (_currentCapacity - _currentOccupancy == 1)
	{
		increaseCapacity();
	}
	*_pointArray[_currentOccupancy++] = pnt;
	return true;
}

bool PointSet::remove(const Point &pnt)
{
	int res = contains(pnt);
	if (res == notFound) return false;
	delete _pointArray[res];
	_pointArray[res] = _pointArray[_currentOccupancy - 2];
	_pointArray[_currentOccupancy - 2] = _pointArray[_currentOccupancy - 1];
	_currentCapacity--;
	if (_currentOccupancy <= _currentCapacity / 2) decreaseCapacity();
	return true;


}

int PointSet::size() const
{
	return _currentOccupancy;
}

int PointSet::contains(const Point &pPoint) const
{
	for (int i = 0; i < _currentOccupancy; i++)
	{
		if (_pointArray[i] == nullptr)
		{
			continue;
		} else if (*_pointArray[i] == &pPoint)
		{
			return i;
		}
	}
	return notFound;
}

void PointSet::increaseCapacity()
{
	_currentCapacity = _currentCapacity * 2;

	Point **newArray = new Point *[_currentCapacity];
	std::swap_ranges(_pointArray[0], _pointArray[_currentOccupancy], newArray[0]);

	delete[] _pointArray;
	_pointArray = newArray;

}

void PointSet::decreaseCapacity()
{
	_currentCapacity = _currentCapacity / 2;
	Point **newArray = new Point *[_currentCapacity];
	std::fill_n(newArray, _currentCapacity, nullptr);
	std::swap_ranges(_pointArray[0], _pointArray[_currentOccupancy], newArray[0]);

	delete[] _pointArray;
	_pointArray = newArray;


}

bool PointSet::operator==(const PointSet &oPntSt) const
{
	if (this->size() != oPntSt.size())
	{
		return false;
	}
	for (int i = 0; i < this->size(); i++)
	{
		if (oPntSt.contains(*_pointArray[i]) == notFound)
		{
			return false;
		}
	}
	return true;
}

bool PointSet::operator!=(const PointSet &oPntSt) const
{
	return !operator==(oPntSt);
}

PointSet PointSet::operator-(const PointSet &oPntSt) const
{
	PointSet newSet = PointSet(this->size());
	for (int i = 0; i < _currentOccupancy; i++)
	{

		if (oPntSt.contains(*_pointArray[i]) == notFound)
		{
			newSet.add(*_pointArray[i]);
		}
	}
	return newSet;
}

PointSet PointSet::operator&(const PointSet &oPntSt) const
{
	PointSet newSet = PointSet(this->size());
	for (int i = 0; i < _currentOccupancy; i++)
	{

		if (oPntSt.contains(*_pointArray[i]) != notFound)
		{
			newSet.add(*_pointArray[i]);
		}
	}
	return newSet;
}

int PointSet::convexSort()
{
	Point **tempArray = new Point *[_currentOccupancy + 1];
	std::copy(_pointArray, _pointArray + _currentOccupancy, tempArray[1]);
	int minYpos = 1;
	for (int i = 2; i < _currentOccupancy + 1; i++)
	{
		if (tempArray[i]->get_yCord() < tempArray[1]->get_yCord())
		{
			std::swap(tempArray[i], tempArray[1]);
		}
	}
	/*
	let N           = number of points
	let points[N+1] = the array of points
	swap points[1] with the point with the lowest y-coordinate
	sort points by polar angle with points[1]

# We want points[0] to be a sentinel point that will stop the loop.
	let points[0] = points[N]

# M will denote the number of points on the convex hull.
	let M = 1
	for i = 2 to N:
# Find next valid point on convex hull.
	while ccw(points[M-1], points[M], points[i]) <= 0:
	if M > 1:
	M -= 1
# All points are collinear
	else if i == N:
	break
	else
	i += 1

# Update M and swap points[i] to the correct place.
	M += 1
	swap points[M] with points[i]
	 */


	return 0;
}
