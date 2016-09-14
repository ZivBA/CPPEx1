//
// Created by zivben on 8/28/16.
//

#include <sstream>
#include <algorithm>
#include "PointSet.h"

/**
 * default constructor creating the backing array in default size.
 * @return pointer to the new PointSet.
 */
PointSet::PointSet() : PointSet(_initialCapacity)
{

}

/**
 * constructor accepting size argument, creates a new set with the backing array of size "size".
 * @param size size of array to create.
 * @return pointer to new PointSet.
 */
PointSet::PointSet(int const size)
{
	_pointArray = new Point *[size];
	_currentCapacity = size;
	_initArrayOfPnts(_pointArray, _currentCapacity);
}

/**
 * copy constructor.
 * @param oPntSet the other pointSet to copy from
 * @return a pointer to a new PointSet holding all the points of the other pointset.
 */
PointSet::PointSet(const PointSet &oPntSet) : PointSet(oPntSet.size())
{
	*this = oPntSet;
}

/**
 * default destructor.
 * deletes[] the backing array.
 */
PointSet::~PointSet()
{

	for (int i = 0; i < _currentCapacity; i++)
	{
		delete _pointArray[i];
	}
	delete[] _pointArray;

}

/**
 * textual representation of the set.
 * @return a string representing all the points in the set by insertion order
 * (as long as no "remove" calls were made on the set or other sorting calls were made).
 */
std::string PointSet::toString()
{
	std::stringstream ss;
	for (int i = 0; i < this->_currentOccupancy; i++)
	{

		ss << _pointArray[i]->toString() << "\n";

	}
	return ss.str();
}

/**
 * adds a point to the set iff no other points of the same coordinates exist.
 * @param pnt reference to the point being inserted.
 * @return sucess ? true : false;
 */
bool PointSet::add(Point const &pnt)
{
	if (_contains(pnt) != notFound)
	{
		return false;
	}
	if (_currentCapacity - _currentOccupancy == 1)
	{
		_increaseCapacity();
	}
	_pointArray[_currentOccupancy++] = new Point(pnt);
	return true;
}


/**
 * removes a point from the set iff a point of the same coordinates exists in it.
 * @param pnt reference to the removal candidate point.
 * @return sucess ? true : false;
 */

bool PointSet::remove(const Point &pnt)
{
	int res = _contains(pnt);
	if (res == notFound)
	{
		return false;
	}
	delete _pointArray[res];
	if (res != _currentOccupancy - 1)
	{
		_pointArray[res] = _pointArray[_currentOccupancy - 1];
	}
	_currentOccupancy--;
	if (_currentOccupancy < _currentCapacity / 2)
	{
		_decreaseCapacity();
	}
	return true;


}

/**
 * the number of points in the set.
 * @return number of points in the set.
 */
int PointSet::size() const
{
	return _currentOccupancy;
}

/**
 * checks if a point is currently in the set, returns it's index if found or "notFound" else.
 * @param pPoint point to search for.
 * @return index of the point in the backing array or "notFound" flag (-1);
 */
int PointSet::_contains(const Point &pPoint) const
{
	for (int i = 0; i < _currentOccupancy; i++)
	{
		if (_pointArray[i] == nullptr)
		{
			continue;
		}
		else if (*_pointArray[i] == &pPoint)
		{
			return i;
		}
	}
	return notFound;
}

/**
 * private method used for dynamic resizing of the backing array. doubles the capacity of the
 * set and copies the point pointers from the current array to the new one.
 */
void PointSet::_increaseCapacity()
{
	_currentCapacity = _currentCapacity * 2;

	Point **newArray = new Point *[_currentCapacity];
	_initArrayOfPnts(newArray, _currentCapacity);

	std::swap_ranges(_pointArray, _pointArray + _currentOccupancy, newArray);

	delete[] _pointArray;
	_pointArray = newArray;

}

/**
 * private method used for dynamic resizing of the backing array. halves the capacity of the
 * set and copies the point pointers from the current array to the new one.
 */
void PointSet::_decreaseCapacity()
{
	_currentCapacity = _currentCapacity / 2;
	Point **newArray = new Point *[_currentCapacity];
	_initArrayOfPnts(newArray, _currentCapacity);
	std::swap_ranges(_pointArray, _pointArray + _currentOccupancy, newArray);

	delete[] _pointArray;
	_pointArray = newArray;


}

/**
 * asignment operator overload, used to ensure proper copy constructor and asignments.
 * @param oPntSt the RHS pointset being asigned to "this" pointset.
 * @return pointer to "this" pointset after all points were removed and all those from the
 * other pointset were copied in.
 */
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

/**
 * equality operator overload
 * @param oPntSt the RHS pointset with which "this" pointeset is being compared.
 * @return true iff "this" pointset holds exactly the same points as "that" one.
 */
bool PointSet::operator==(const PointSet &oPntSt) const
{
	if (this->size() != oPntSt.size())
	{
		return false;
	}
	for (int i = 0; i < this->size(); i++)
	{
		if (_pointArray[i] != nullptr && oPntSt._contains(*_pointArray[i]) == notFound)
		{
			return false;
		}
	}
	return true;
}

/**
 * inequality operator overload
 * @param oPntSt the RHS pointset being compared with
 * @return true iff this pointset is not == other pointset.
 */
bool PointSet::operator!=(const PointSet &oPntSt) const
{
	return !operator==(oPntSt);
}

/**
 * subtraction operator overload.
 * @param oPntSt RHS pointset to be "substracted" from this one.
 * @return a new pointset holding all points in "this" pointset that are not in "other" pointset
 */
PointSet PointSet::operator-(const PointSet &oPntSt) const
{
	PointSet newSet = PointSet(this->size());
	for (int i = 0; i < _currentOccupancy; i++)
	{

		if (_pointArray[i] != nullptr && oPntSt._contains(*_pointArray[i]) == notFound)
		{
			newSet.add(*_pointArray[i]);
		}
	}
	return newSet;
}

/**
 * intersection of sets
 * @param oPntSt the RHS pointset to intersect with "this"
 * @return a new PointSet holding all the points in "this" set that *are* in the "other" set.
 */
PointSet PointSet::operator&(const PointSet &oPntSt) const
{
	PointSet newSet = PointSet(this->size());
	for (int i = 0; i < _currentOccupancy; i++)
	{

		if (oPntSt._contains(*_pointArray[i]) != notFound)
		{
			newSet.add(*_pointArray[i]);
		}
	}
	return newSet;
}

/**
 * a comparator used to sort the set by poloar angle from an anchor point.
 * one MUST set the anchorpoint before using.
 * @param a first point to compare
 * @param b second point to compare
 * @return false iff point a has a larger reference angle than point b.
 */
bool PointSet::polarAngleComparator(const Point *a, const Point *b)
{

	int order = _ccw(_anchPnt, *a, *b);
	return order == 0 ? _sqrDist(&_anchPnt, a) < _sqrDist(&_anchPnt, b) : order < 0;
}

/**
 * a comparator used to sort the set by x coords (first criteria), then y (second criteria)
 * @param a first point to compare
 * @param b second point to compare
 * @return ture iff a.x < b.x or (a.x == b.x && a.y<b.y)
 */

bool PointSet::xyComparator(const Point *a, const Point *b)
{
	return a->getXcord() < b->getXcord() ? true :
	       a->getXcord() == b->getXcord() ? a->getYcord() < b->getYcord() : false;
}

/**
 * returns the distance between two points;
 * @param a first point
 * @param b second point
 * @return an integer value of the distance between the points.
 */
int PointSet::_sqrDist(const Point *a, const Point *b)
{
	int dx = a->getXcord() - b->getXcord(), dy = a->getYcord() - b->getYcord();
	return dx * dx + dy * dy;
}


/**
 * checks if a third point (p3) is a clockwise or counter-clockwise turn from the two
* preceding points (p1, p2). used for the graham-scan algorithm.
* @param p1 input point 1
* @param p2 input point 2
* @param p3 input point 3
* @return an integer: Three points are a counter-clockwise turn if ccw > 0, clockwise if
*	ccw < 0, and collinear if ccw = 0
*/
int PointSet::_ccw(const Point &p1, const Point &p2, const Point &p3)
{
	return ((p2.getYcord() - p1.getYcord()) * (p3.getXcord() - p1.getXcord()) -
	        (p2.getXcord() - p1.getXcord()) * (p3.getYcord() - p1.getYcord()));


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
		if (points[i]->getYcord() < points[1]->getYcord())
		{
			std::swap(points[i], points[1]);
		}
		else if (points[i]->getYcord() == points[1]->getYcord())
		{
			if (points[i]->getXcord() < points[1]->getXcord())
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
		while (_ccw(*points[M - 1], *points[M], *points[i]) >= 0)
		{
			if (M > 1)
			{
				M--;
			}
			else if (i == N)
			{
				break;
			}
			else
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

/**
 * simple loop to initialize an array with nullptr.
 * @param pPoint the array to initialize
 * @param size the size of the array.
 */
void PointSet::_initArrayOfPnts(Point **pPoint, const int size)
{
	for (int i = 0; i < size; i++)
	{
		pPoint[i] = nullptr;
	}
}

/**
 * if one wants his pointset sorted, say, for printing, then this is the way to go.
 */
void PointSet::sortXY()
{
	std::sort(_pointArray, (_pointArray + _currentOccupancy), xyComparator);
}
