#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <Windows.h>

using namespace std;

enum Direction {
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
};

class Player {
    private:
        vector<COORD> body;
        COORD head;
        int len;
        Direction dir;
    public:
        Player(COORD _head);
        void SetDir(Direction _dir);
        vector<COORD> GetBody();
        bool Move(COORD pointPos);
        int GetLen();
};

#endif