#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "../include/Player.hpp"

#define MapSize 32

using namespace std;

void Init();
void ResetScreen();
void DrawWall();
void Draw();
void DrawPlayer();
void DetectInput();
void MoveCursor(int x, int y);

char screen[MapSize][MapSize + 1];
Player p({MapSize / 2,MapSize / 2});

int main() {
    Init();
    DrawWall();
    while(1){
        DetectInput();
        if(p.Move()) {
            Draw();
        }
        else {
            system("pause");
            break;
        }

        Sleep(500);
    }
    return 0;
}

void Init() {
    // 창 크기 고정 및 제목 설정
    system("mode con: cols=34 lines=34 | title Snake");

    // 커서 숨김
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // screen 초기화
    ResetScreen();
}

void ResetScreen()
{
    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0; j < MapSize; j++)
        {
            screen[i][j] = ' ';
        }
        screen[i][MapSize] = '\0';
    }
}

void DrawWall() {
    // 상하 벽 생성
    for(int i = 1; i < MapSize + 1; i++) {
        MoveCursor(i,0);
        cout << "-";
        MoveCursor(i, MapSize + 1);
        cout << "-";
    }
    // 좌우 벽 생성
    for(int i = 1; i < MapSize + 1; i++) {
        MoveCursor(0,i);
        cout << "|";
        MoveCursor(MapSize + 1, i);
        cout << "|";
    }
    // 꼭짓점 생성
    MoveCursor(0,0);
    cout << "0";
    MoveCursor(MapSize + 1,0);
    cout << "0";
    MoveCursor(0,MapSize + 1);
    cout << "0";
    MoveCursor(MapSize + 1,MapSize + 1);
    cout << "0";
}

void Draw() {
    DrawPlayer();

    for(int i = 0; i < MapSize; i++) {
        MoveCursor(1, i + 1);
        cout << screen[i];
    }
}

void DrawPlayer()
{
    vector<COORD> body = p.GetBody();
    ResetScreen();
    for (int i = 0; i < body.size(); i++)
    {
        screen[body[i].Y][body[i].X] = 'O';
    }
}

void DetectInput()
{
    if (_kbhit())
    {
        char c = _getch();
        if (c == -32)
        {
            c = _getch();
            switch (c)
            {
            case Direction::LEFT:
                p.SetDir(Direction::LEFT);
                break;
            case Direction::RIGHT:
                p.SetDir(Direction::RIGHT);
                break;
            case Direction::UP:
                p.SetDir(Direction::UP);
                break;
            case Direction::DOWN:
                p.SetDir(Direction::DOWN);
                break;
            }
        }
    }
}

void MoveCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
