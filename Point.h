//
// Created by zivben on 8/28/16.
//

#include <string>
#include <math.h>
#ifndef EX1_POINT_H
#define EX1_POINT_H


class Point
{
private:

	int _xCord;
	int _yCord;
	std::string _stringRep;

public:
	Point();

	Point(int x, int y);

	int get_xCord() const;

	int get_yCord() const;

	Point(const Point &oPnt);

	~Point();

	std::string toString() const;

	void set(int x, int y);

	bool operator==(const Point *oPnt) const;

	int operator*(const Point &p2) const;

	Point operator=(const Point &p2);

	double norm() const;


};


#endif //EX1_POINT_H
