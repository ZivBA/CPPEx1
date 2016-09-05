/**
 * Simple test for the PointSet implementation
 */
#include <iostream>
#include "PointSet.h"

#define NUM_ARRAYS 4

/**
 * POC class showing all the PointSet Operators
 * it's a tester file (copied from what Dany Barash published in the moodle) that tessts the operators
 * and outputs an error if an operator doesnt do what it's supposed to do.
 * @return
 */
int main()
{

	/**
	 * create an array of pointsets, populate each set with some points.
	 */
	PointSet setsArr[NUM_ARRAYS];
	Point pnt1 = Point(6, 5);
	Point pnt2 = Point(7, 6);
	Point pnt3 = Point(6, 5);
	Point pnt4 = Point(7, 6);
	Point pnt5 = Point(8, 2);
	Point pnt6 = Point(9, -2);
	Point pnt7 = Point(10, -2);
	Point pnt8 = Point(6, 5);
	Point pnt9 = Point(7, 6);

	setsArr[0].add(pnt1);
	setsArr[0].add(pnt2);
	setsArr[1].add(pnt3);
	setsArr[1].add(pnt4);
	setsArr[1].add(pnt5);
	setsArr[2].add(pnt6);
	setsArr[2].add(pnt7);
	setsArr[3].add(pnt8);
	setsArr[3].add(pnt9);

//	setsArr[0].remove(pnt1);
//	setsArr[0].remove(pnt2);


	/**

	* test the != operator. set 0 and set 3 are identical and should return false, if true - error.
	*/
	if (setsArr[0] != setsArr[3])
	{
		std::cout << "ERROR: Fail test comparing weight unEq" << std::endl;
		return 1;
	}

	/**
	 * test == operator. sets 0 and 1 are different, so should return false, if true - error.
	 */
	if (setsArr[0] == setsArr[1])
	{
		std::cout << "ERROR: Fail test comparing weight eq" << std::endl;
		return 1;
	}

	/**
	 * test the - operator (and implicitly, the copy constructor.)  set 1 contains all the points of
	 * set 0, so the operator must return an empty set. if the size of the returned set is not 0 - error.
	 */
	PointSet min = setsArr[0] - setsArr[1];
	if (min.size() != 0)
	{
		std::cout << "ERROR: Fail test Minus" << std::endl;
		return 1;
	}

	/**
	 * test the & operator. sets 0 and 2 are disjoint, so the operator must return an empty set.
	 * if the size of the new set is not 0 - error.
	 */
	PointSet intersect = setsArr[0] & setsArr[2];
	if (intersect.size() != 0)
	{
		std::cout << "ERROR: Fail test Intersection" << std::endl;
		return 1;
	}

	std::cout << "Pass basic binary MySet tests." << std::endl;

	return 0;
}
