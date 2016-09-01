//
// Created by zivben on 8/28/16.
//

#include "ConvexHull.h"
#include <iostream>
#include <sstream>

int main()
{

	PointSet preConvexSet = PointSet();
	PointSet postConvex;
	std::string line;

	int coords[2] = {0, 0};
//	char comma = 0;
	Point const *tempPointHolder;
	while (!std::cin.eof())
	{
		std::cin >> line;
		sscanf(line.c_str(), "%i,%i", &coords[0], &coords[1]);
		tempPointHolder = new Point(coords[0], coords[1]);
		preConvexSet.add(*tempPointHolder);

		line = "";

	}
//	postConvex = PointSet(preConvexSet.size());


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
int ccw(const Point &p1, const Point &p2, const Point &p3)
{
	return (p2.get_xCord() - p1.get_xCord()) * (p3.get_yCord() - p1.get_yCord()) -
	       (p2.get_yCord() - p1.get_yCord()) * (p3.get_xCord() - p1.get_xCord());
}
