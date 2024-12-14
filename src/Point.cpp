#include <Windows.h>
#include <time.h>
#include <random>

#include "../include/Point.hpp"

#define MapSize 32

COORD Point::GetPos() {
    return pos;
}

Point::Point()
{
    srand(time(NULL));
    
    int x = rand() % MapSize;
    int y = rand() % MapSize;
    pos = {x, y};
}

