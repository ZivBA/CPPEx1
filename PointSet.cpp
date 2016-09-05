//
// Created by zivben on 8/28/16.
//

#include <sstream>
#include <algorithm>
#include "PointSet.h"

PointSet::PointSet() : PointSet(_initialCapacity)
{

}

PointSet::PointSet(int const size)
{
	_pointArray = new Point *[size];
	_currentCapacity = size;
	initArrayOfPnts(_pointArray, _currentCapacity);
}

PointSet::PointSet(const PointSet &PntSt) : PointSet(PntSt.size())
{
	copyToMyArrayFrom(PntSt);
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

		ss << _pointArray[i]->toString() << "\n";

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
	if (res != _currentOccupancy - 1)
	{
		_pointArray[res] = _pointArray[_currentOccupancy - 2];
		_pointArray[_currentOccupancy - 2] = _pointArray[_currentOccupancy - 1];
	}
	_currentOccupancy--;
	if (_currentOccupancy < _currentCapacity / 2) decreaseCapacity();
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
	initArrayOfPnts(newArray, _currentCapacity);

	std::swap_ranges(_pointArray, _pointArray + _currentOccupancy, newArray);

	delete[] _pointArray;
	_pointArray = newArray;

}

void PointSet::decreaseCapacity()
{
	_currentCapacity = _currentCapacity / 2;
	Point **newArray = new Point *[_currentCapacity];
	initArrayOfPnts(newArray, _currentCapacity);
	std::swap_ranges(_pointArray, _pointArray + _currentOccupancy, newArray);

	delete[] _pointArray;
	_pointArray = newArray;


}

PointSet PointSet::operator=(const PointSet &oPntSt)
{
	if (this == &oPntSt)
	{
		return *this;
	}
	for (int i = 0; i < _currentCapacity; i++)
	{
		delete _pointArray[i];
	}
	delete _pointArray;

	copyToMyArrayFrom(oPntSt);

	return *this;
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


bool PointSet::cmp(const Point *a, const Point *b)
{
	return ((_anchPnt * *a) / _anchPnt.norm() * a->norm()) <=
	       ((_anchPnt * *b) / _anchPnt.norm() * b->norm());
}

int PointSet::convexSort()
{

	// let N           = number of points
	int N = _currentOccupancy;
	// let tempArray[N+1] = copy of the array of points shifted by 1
	Point **tempArray = new Point *[N + 1];
	initArrayOfPnts(tempArray, N + 1);
	//swap points[0] with the point with the lowest y-coordinate
	for (int i = 1; i < N; i++)
	{
		if (_pointArray[i]->get_yCord() < _pointArray[0]->get_yCord())
		{
			std::swap(_pointArray[i], _pointArray[0]);
		} else if (_pointArray[i]->get_yCord() == _pointArray[0]->get_yCord() &&
		           _pointArray[i]->get_xCord() < _pointArray[0]->get_xCord())
		{
			std::swap(_pointArray[i], _pointArray[0]);
		}
	}

	_anchPnt = *_pointArray[0];

	//sort points by polar angle with points[1]
	sortMe();
	std::copy(_pointArray, _pointArray + N, tempArray + 1);

	//We want points[0] to be a sentinel point that will stop the loop.
	tempArray[0] = tempArray[N];

	//M will denote the number of points on the convex hull.
	int M = 1;
	for (int i = 2; i < N; i++)
	{
		while (ccw(*tempArray[M - 1], *tempArray[M], *tempArray[i]) >= 0)
		{
			if (M > 1)
			{
				M--;
			} else if (i == _currentOccupancy)
			{
				break;
			} else
			{
				i++;
			}
		}
		M++;

		std::swap(tempArray[M], tempArray[i]);
	}

	_currentOccupancy = M + 1;
	delete[] _pointArray;
	_pointArray = new Point *[_currentOccupancy];
	initArrayOfPnts(_pointArray, _currentCapacity);
	std::copy(tempArray + 1, tempArray + _currentOccupancy + 1, _pointArray);


	return 0;
}

/**
 * copied CCW code from WIKI:
 * Three points are a counter-clockwise turn if ccw > 0, clockwise if
 *	ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
 *	gives twice the signed  area of the triangle formed by p1, p2 and p3.
 * @param p1 first point
 * @param p2 second point
 * @param p3 third point
 * @return sign of CCW of three points.
 */
int PointSet::ccw(const Point &p1, const Point &p2, const Point &p3)
{
	return ((p2.get_xCord() - p1.get_xCord()) * (p3.get_yCord() - p1.get_yCord()) -
	        (p2.get_yCord() - p1.get_yCord()) * (p3.get_xCord() - p1.get_xCord()));
}

void PointSet::initArrayOfPnts(Point **pPoint, const int size)
{
	for (int i = 0; i < size; i++)
	{
		pPoint[i] = new Point();
	}
}

void PointSet::sortMe()
{
	std::sort(_pointArray, (_pointArray + _currentOccupancy - 1), cmp);
}

void PointSet::copyToMyArrayFrom(const PointSet &PntSt)
{
	for (int i = 0; i < PntSt.size(); i++)
	{
		delete _pointArray[i];
		_pointArray[i] = PntSt._pointArray[i];
	}
}
