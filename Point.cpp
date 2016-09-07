//
// Created by zivben on 8/28/16.
//

#include <tgmath.h>
#include "Point.h"

/**
 * default constructor
 * @return empty new Point "0,0";
 */
Point::Point()
{
	_xCord = 0;
	_yCord = 0;
}

/**
 * ctor getting x,y coordinates
 * @param x the x coordinate
 * @param y the y coordinate
 * @return new Point "x,y";
 */
Point::Point(int x, int y)
{
	set(x, y);
}

/**
 * copy ctor
 * @param oPnt other Point reference to copy from;
 * @return new Point with the x,y coords of the Other Point.
 */
Point::Point(const Point &oPnt) : Point(oPnt._xCord, oPnt._yCord)
{

}

/**
 * equal operator overload.
 * @param oPnt the point to compare against.
 * @return true iff the string representation of both points is the same. (math set equality)
 */
void Point::set(int x, int y)
{
	_xCord = x;
	_yCord = y;
	_stringRep = std::to_string(_xCord) + "," + std::to_string(_yCord);
}

/**
 * default destructor, zeros the coordinates and the string representation.
 */
Point::~Point()
{
	_xCord = 0;
	_yCord = 0;
	_stringRep = "";
}

/**
 * toString method returns the string representation of the Point object.
 * @return a String of form <x,y>\n;
 */
std::string Point::toString() const
{
	return _stringRep;
}

/**
 * equal operator overload.
 * @param oPnt the point to compare against.
 * @return true iff the string representation of both points is the same. (math set equality)
 */
bool Point::operator==(const Point *oPnt) const
{
	return this->_stringRep.compare(oPnt->_stringRep) == 0;
}

/**
 * multiplication operator overload, basically "dot-product" of two points.
 * @param p2 the RHS point in the p1*p2 expression
 * @return dot product of two points.
 */
int Point::operator*(const Point &p2) const
{
	return (this->_xCord * p2._xCord + this->_yCord * p2._yCord);
}

/**
 * the norm of the point, or the vector from '0,0' to 'this'.
 * @return a double denoting the "length" of the vector.
 */
double Point::norm() const
{
	return sqrt(((*this) * (*this)));
}

/**
	 * getters for x and y coordinates.
	 * @return
	 */
int Point::get_xCord() const
{
	return _xCord;
}

/**
	 * getters for x and y coordinates.
	 * @return
	 */
int Point::get_yCord() const
{
	return _yCord;
}

/**
 * asignment operator overload for proper copy constructor
 * @param p2 reference of the RHS point to asign to "this"
 * @return pointer to "this" after being asigned the values of p2
 */
Point Point::operator=(const Point &p2)
{
	if (this == &p2)
	{
		return *this;
	}
	set(p2._xCord, p2._yCord);
	return *this;

}

