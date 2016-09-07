//
// Created by zivben on 8/28/16.
//

#include <iostream>
#include <sstream>
#include "PointSet.h"

int MINIMAL_SIZE_FOR_CONVEX = 3;

int main()
{

	PointSet preConvexSet = PointSet();
	PointSet *postConvex;
	std::string line;

	int coords[2] = {0, 0};
//	char comma = 0;
	Point const *tempPointHolder;
	while (!std::cin.eof())
	{
		std::cin >> line;
		if (line == "DDDD")
		{
			break;
		}
		if (line == "")
		{
			continue;
		}
		sscanf(line.c_str(), "%i,%i", &coords[0], &coords[1]);
		tempPointHolder = new Point(coords[0], coords[1]);
		preConvexSet.add(*tempPointHolder);
		delete tempPointHolder;
		line = "";

	}
	if (preConvexSet.size() < MINIMAL_SIZE_FOR_CONVEX)
	{
		postConvex = &preConvexSet;
	} else
	{
		postConvex = preConvexSet.convexSort();
	}
	postConvex->sortXY();
	std::cout << "result\n" << postConvex->toString();
	delete postConvex;


	return 0;
}

