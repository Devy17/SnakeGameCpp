#include "../include/Player.hpp"

#define MapSize 32

Player::Player(COORD _head) {
    head = _head;
    len = 1;
    body.push_back(head);
    dir = UP;
}

void Player::SetDir(Direction _dir){
    // 같은 축으로는 이동 불가
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
    
    // 벽에 부딫히면 게임 오버
    if (head.X + dx < 0 || head.X + dx >= MapSize ||
        head.Y + dy < 0 || head.Y + dy >= MapSize) {
            return false;
    }


    // 머리가 움직였을 때 몸체와 충돌하는 지 확인하기 위함.
    body[0].X += dx;
    body[0].Y -= dy;

    head = body[0];

    for(int i =1; i < body.size(); i++) {
        if(head.X == body[i].X && head.Y == body[i].Y) return false;

        body[i].X += dx;
        body[i].Y -= dy;
    }

    

    return true;
}