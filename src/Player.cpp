#include "../include/Player.hpp"

#define MapSize 32

Player::Player(COORD _head) {
    head = _head;
    len = 1;
    body.push_back(head);
    dir = UP;
}

void Player::SetDir(Direction _dir){
    switch(_dir) {
        case Direction::LEFT:
            if (dir == Direction::RIGHT) return;
            break;
        case Direction::RIGHT:
            if (dir == Direction::LEFT) return;
            break;
        case Direction::UP:
            if (dir == Direction::DOWN) return;
            break;
        case Direction::DOWN:
            if (dir == Direction::UP) return;
            break;
    }

    dir = _dir;
}

vector<COORD> Player::GetBody() {
    return body;
}

bool Player::Move() {
    int dx = 0;
    int dy = 0;

    switch(dir) {
        case Direction::UP:
            dy++; break;
        case Direction::DOWN:
            dy--; break;
        case Direction::RIGHT:
            dx++; break;
        case Direction::LEFT:
            dx--; break; 
    }
    
    if (head.X + dx < 0 || head.X + dx > MapSize ||
        head.Y + dy < 0 || head.Y + dy > MapSize) {
            return false;
    }




    for(int i =0; i < body.size(); i++) {
        

        body[i].X += dx;
        body[i].Y -= dy;
    }

    head.X = body[0].X;
    head.Y = body[0].Y;

    return true;
}