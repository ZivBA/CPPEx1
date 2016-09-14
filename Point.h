//
// Created by zivben on 8/28/16.
//

#include <string>
#include <math.h>
#ifndef EX1_POINT_H
#define EX1_POINT_H

/**
 * This class defines a Point in the cartesian space
 */
class Point
{
private:

	//Integer Coordinates and the string representation of them.
	int _xCord;
	int _yCord;
	std::string _stringRep;

public:
	/**
	 * default constructor
	 * @return empty new Point "0,0";
	 */
	Point();

	/**
	 * ctor getting x,y coordinates
	 * @param x the x coordinate
	 * @param y the y coordinate
	 * @return new Point "x,y";
	 */
	Point(int x, int y);

	/**
	 * getters for x and y coordinates.
	 * @return
	 */
	int getXcord() const;

	/**
	 * getters for x and y coordinates.
	 * @return
	 */
	int getYcord() const;

	/**
	 * copy ctor
	 * @param oPnt other Point reference to copy from;
	 * @return new Point with the x,y coords of the Other Point.
	 */
	Point(const Point &oPnt);

	/**
	 * default destructor, zeros the coordinates and the string representation.
	 */
	~Point();

	/**
	 * toString method returns the string representation of the Point object.
	 * @return a String of form <x,y>\n;
	 */
	std::string toString() const;

	/**
	 * this method sets new x,y coordinates for an existing point, also rewrites the string_rep
	 * @param x
	 * @param y
	 */
	void set(int x, int y);

	/**
	 * equal operator overload.
	 * @param oPnt the point to compare against.
	 * @return true iff the string representation of both points is the same. (math set equality)
	 */
	bool operator==(const Point *oPnt) const;

	/**
	 * multiplication operator overload, basically "dot-product" of two points.
	 * @param p2 the RHS point in the p1*p2 expression
	 * @return dot product of two points.
	 */
	int operator*(const Point &p2) const;

	/**
	 * asignment operator overload for proper copy constructor
	 * @param p2 reference of the RHS point to asign to "this"
	 * @return pointer to "this" after being asigned the values of p2
	 */
	Point operator=(const Point &p2);

	/**
	 * the norm of the point, or the vector from '0,0' to 'this'.
	 * @return a double denoting the "length" of the vector.
	 */
	double norm() const;


};


#endif //EX1_POINT_H
