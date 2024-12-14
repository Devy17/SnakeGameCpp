#ifndef POINT_H
#define POINT_H

#include <Windows.h>

class Point {
    private:
        COORD pos;

    public:
        COORD GetPos();
        Point();
        ~Point() {};
};

#endif