//
// Created by zivben on 8/28/16.
//

#include <tgmath.h>
#include "Point.h"

Point::Point()
{
	_xCord = 0;
	_yCord = 0;
}

Point::Point(int x, int y)
{
	set(x, y);
}

Point::Point(const Point &oPnt) : Point(oPnt._xCord, oPnt._yCord)
{

}

void Point::set(int x, int y)
{
	_xCord = x;
	_yCord = y;
	_stringRep = std::to_string(_xCord) + "," + std::to_string(_yCord);
}

Point::~Point()
{
	_xCord = 0;
	_yCord = 0;
	_stringRep = "";
}

std::string Point::toString() const
{
	return _stringRep;
}

bool Point::operator==(const Point *oPnt) const
{
	return this->_stringRep.compare(oPnt->_stringRep) == 0;
}


int Point::operator*(const Point &p2) const
{
	return (this->_xCord * p2._xCord + this->_yCord * p2._yCord);
}

double Point::norm() const
{
	return sqrt(((*this) * (*this)));
}

int Point::get_xCord() const
{
	return _xCord;
}

int Point::get_yCord() const
{
	return _yCord;
}

