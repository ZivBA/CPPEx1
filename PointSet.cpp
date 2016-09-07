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

PointSet::PointSet(const PointSet &oPntSet) : PointSet(oPntSet.size())
{
	*this = oPntSet;
}

PointSet::~PointSet()
{

	for (int i = 0; i < _currentCapacity; i++)
	{
		delete _pointArray[i];
	}
	delete[] _pointArray;

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
	_pointArray[_currentOccupancy++] = new Point(pnt);
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
	for (int i = 0; i < oPntSt.size(); i++)
	{
		delete _pointArray[i];
		*_pointArray[i] = *oPntSt._pointArray[i];
	}

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
		if (_pointArray[i] != nullptr && oPntSt.contains(*_pointArray[i]) == notFound)
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

		if (_pointArray[i] != nullptr && oPntSt.contains(*_pointArray[i]) == notFound)
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


bool PointSet::polarAngleComparator(const Point *a, const Point *b)
{

	int order = ccw(_anchPnt, *a, *b);
	return order == 0 ? sqrDist(&_anchPnt, a) < sqrDist(&_anchPnt, b) : order < 0;
}

bool PointSet::xyComparator(const Point *a, const Point *b)
{
	return a->get_xCord() < b->get_xCord() ? true :
	       a->get_xCord() == b->get_xCord() ? a->get_yCord() < b->get_yCord() : false;
}

int PointSet::sqrDist(const Point *a, const Point *b)
{
	int dx = a->get_xCord() - b->get_xCord(), dy = a->get_yCord() - b->get_yCord();
	return dx * dx + dy * dy;
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
	return ((p2.get_yCord() - p1.get_yCord()) * (p3.get_xCord() - p1.get_xCord()) -
	        (p2.get_xCord() - p1.get_xCord()) * (p3.get_yCord() - p1.get_yCord()));


}

/**
 * the convexhull algorithm as it appears in:
 * https://en.wikipedia.org/wiki/Graham_scan
 * The first step in this algorithm is to find the point with the lowest y-coordinate. If the
 * lowest y-coordinate exists in more than one point in the set, the point with the lowest
 * x-coordinate out of the candidates should be chosen. Call this point P. This step takes O(n),
 * where n is the number of points in question.
 * Next, the set of points must be sorted in increasing order of the angle they and the point P make
 * with the x-axis. Any general-purpose sorting algorithm is appropriate for this, for example
 * heapsort (which is O(n log n)).
 * Sorting in order of angle does not require computing the angle. It is possible to use any
 * function  of the angle which is monotonic in the interval {\displaystyle [0,\pi )} [0,\pi ) .
 * The cosine is easily computed using the dot product, or the slope of the line may be used. If
 * numeric precision is at a stake, the comparison function used by the sorting algorithm can use
 * the sign of the cross product to determine relative angles.
 * The algorithm proceeds by considering each of the points in the sorted array in sequence.  For
 * each point, it is first determined whether traveling from the two points immediately preceding
 * this point constitutes making a left turn or a right turn. If a right turn, the second-to-last
 * point is not part of the convex hull, and lies 'inside' it. The same determination is then made
 * for the set of the latest point and the two points that immediately precede the point found to
 * have been inside the hull, and is repeated until a "left turn" set is encountered, at which
 * point  the algorithm moves on to the next point in the set of points in the sorted array minus
 * any  points that were found to be inside the hull; there is no need to consider these points
 * again.  (If at any stage the three points are collinear, one may opt either to discard or to
 * report  it, since in some applications it is required to find all points on the boundary of the
 * convex hull.)
 * Again, determining whether three points constitute a "left turn" or a "right turn" does not
 * require  computing the actual angle between the two line segments, and can actually be achieved
 * with simple arithmetic only. For three points  P_{1}=(x_{1},y_{1}), P_{2}=(x_{2},y_{2}) and
 * P_{3}=(x_{3},y_{3}), simply compute the z-coordinate of the cross product of the two vectors
 * {P_{1}P_{2}} and  {P_{1}P_{3}}, which is given by the expression  (x_{2}-x_{1})(y_{3}-y_{1})-
 * (y_{2}-y_{1})(x_{3}-x_{1}). If the result is 0, the points are collinear; if it is positive,
 * the three points constitute a "left turn" or counter-clockwise orientation, otherwise a "right
 * turn" or clockwise orientation (for counter-clockwise numbered points).
 * This process will eventually return to the point at which it started, at which point the
 * algorithm  is completed and the stack now contains the points on the convex hull in
 * counterclockwise  order.
 * Sorting the points has time complexity O(n log n). While it may seem that the time complexity
 * of the loop is O(n^2), because for each point it goes back to check if any of the previous
 * points make a "right turn", it is actually O(n), because each point is considered at most twice
 * in some sense. Each point can appear only once as a point (x_2,y_2) in a "left turn" (because
 * the algorithm advances to the next point (x_3,y_3) after that), and as a point (x_2,y_2) in a
 * "right turn" (because the point (x_2,y_2) is removed). The overall time complexity is therefore
 * O(n log n), since the time to sort dominates the time to actually compute the convex hull.
 * @return a new PointSet with just the hull points.
 */
PointSet *PointSet::convexSort()
{
	//let N = number of points:
	int N = _currentOccupancy;
	//let points[N+1] = the array of points.
	Point **points = new Point *[N + 1];
	std::copy(_pointArray, _pointArray + N, points + 1);
	//swap points[1] with the point with lowest y-coordinate;
	for (int i = 2; i < N + 1; i++)
	{
		if (points[i]->get_yCord() < points[1]->get_yCord())
		{
			std::swap(points[i], points[1]);
		} else if (points[i]->get_yCord() == points[1]->get_yCord())
		{
			if (points[i]->get_xCord() < points[1]->get_xCord())
			{
				std::swap(points[i], points[1]);

			}
		}
	}
	//sort points by polar angle with points[1]
	_anchPnt = *points[1];
	std::sort(points + 1, points + N + 1, polarAngleComparator);
	// We want points[0] to be a sentinel point that will stop the loop.
	points[0] = points[N];

	//M will denote the number of points on the convex hull.

	int M = 1;
	for (int i = 2; i <= N; i++)
	{
		while (ccw(*points[M - 1], *points[M], *points[i]) >= 0)
		{
			if (M > 1)
			{
				M--;
			} else if (i == N)
			{
				break;
			} else
			{
				i++;
			}
		}
		M++;
		std::swap(points[i], points[M]);
	}

	PointSet *newSet = new PointSet(M);
	for (int i = 0; i <= M; i++)
	{
		newSet->add(*points[i]);
	}
	delete[] points;
	return newSet;


}

void PointSet::initArrayOfPnts(Point **pPoint, const int size)
{
	for (int i = 0; i < size; i++)
	{
		pPoint[i] = nullptr;
	}
}

void PointSet::sortXY()
{
	std::sort(_pointArray, (_pointArray + _currentOccupancy), xyComparator);
}

//void PointSet::copyToMyArrayFrom(const PointSet &PntSt)
//{
//	for (int i = 0; i < PntSt.size(); i++)
//	{
//		delete _pointArray[i];
//		_pointArray[i] = PntSt._pointArray[i];
//	}
//}
