//
// Created by zivben on 8/28/16.
//

#include <string>
#ifndef EX1_POINT_H
#define EX1_POINT_H


class Point {
private:

    int _xCord;
    int _yCord;
    std::string _stringRep;

public:
    Point();
    Point(int x, int y);
    Point(const Point &oPnt);
    ~Point();
    std::string toString();
    void set(int x, int y);

    bool operator==(const Point oPnt) const;
};


#endif //EX1_POINT_H
