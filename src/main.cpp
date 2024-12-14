#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <random>
#include "../include/Player.hpp"

#define MapSize 20

using namespace std;

void Init();
int NextMove(long start, COORD pointPos);
void ResetScreen();
// void DrawWall();
void Draw();
COORD DrawPoint();
void DrawPlayer();
void DetectInput();
void MoveCursor(int x, int y);

char screen[MapSize][MapSize + 1];
Player p({MapSize / 2,MapSize / 2});
COORD pointPos = {-1, -1};

int main() {
    while(true) {
        Init();
        pointPos = DrawPoint();

        long start = (long)clock();
        while(true){
            // 키보드 입력 감지
            DetectInput();
            
            // 정해진 시간마다 움직임 수행
            int isWaitOrEnd = NextMove(start, pointPos);
            if(isWaitOrEnd == -1) break;
            else if(isWaitOrEnd == 0) {
                start = clock();
            }
        }

        screen[pointPos.Y][pointPos.X] = ' ';
        MoveCursor(pointPos.X + 1, pointPos.Y + 1);
        cout << ' ';

        Sleep(3000);
        ResetScreen();
        MoveCursor(MapSize/2 - 3, MapSize/2 -1);
        cout << "Retry?";
        MoveCursor(MapSize/2 - 3, MapSize/2);
        cout << "(y/n)";
        MoveCursor(MapSize/2 - 1, MapSize/2 + 1);
        char r; r = _getch();
        if(r != 'y') break;
        else {
            p.SetInitial({MapSize / 2,MapSize / 2});
            pointPos = {-1, -1};
        }
    }
    return 0;
}

int NextMove(long start, COORD _pointPos)
{
    // Delay
    while(clock() - start < 0.5f * CLOCKS_PER_SEC) return 1;

    int len = p.GetLen();
    if (p.Move(_pointPos))
    {
        // 포인트를 먹었다면
        if(len != p.GetLen()) {
            if(len == MapSize * MapSize) {
                ResetScreen();
                MoveCursor(MapSize/2 - 2, MapSize/2 -1);
                cout << "Clear";
                return -1;
            }

            pointPos = DrawPoint();
        }
        Draw();
        return 0;
    }
    else
    {
        // 끝남 처리
        ResetScreen();
        MoveCursor(MapSize/2 - 4, MapSize/2 -1);
        cout << "Game Over";
        return -1;
    }
}

void Init() {
    // 창 크기 고정 및 제목 설정
    system("mode con: cols=22 lines=22 | title Snake");

    // 커서 숨김
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // 벽 그리기

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

    // screen 초기화
    ResetScreen();
}

void DetectInput()
{
    // 입력 확인
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

void ResetScreen()
{
    for (int i = 0; i < MapSize; i++)
    {
        for (int j = 0; j < MapSize; j++)
        {
            if(screen[i][j] == '@') continue;
            screen[i][j] = ' ';
        }
        screen[i][MapSize] = '\0';
    }

    for(int i = 0; i < MapSize; i++) {
        MoveCursor(1, i + 1);
        cout << screen[i];
    }
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

COORD DrawPoint() { // 점수를 획득하였을때만
    COORD pos;
    srand(time(NULL));
    while(true) {
        int x = rand() % MapSize;
        int y = rand() % MapSize;
        pos = {x, y};
        bool isSamePos = false;
        vector<COORD> body = p.GetBody();
        for(int i =0; i < body.size(); i++){
            if(pos.X == body[i].X && pos.Y == body[i].Y) {
                isSamePos = true;
                break;
            }
        }

        if(!isSamePos) break;
    }
    
    screen[pos.Y][pos.X] = '@';
    return pos;
}

void MoveCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// void DrawWall() {
//     // 상하 벽 생성
//     for(int i = 1; i < MapSize + 1; i++) {
//         MoveCursor(i,0);
//         cout << "-";
//         MoveCursor(i, MapSize + 1);
//         cout << "-";
//     }
//     // 좌우 벽 생성
//     for(int i = 1; i < MapSize + 1; i++) {
//         MoveCursor(0,i);
//         cout << "|";
//         MoveCursor(MapSize + 1, i);
//         cout << "|";
//     }
//     // 꼭짓점 생성
//     MoveCursor(0,0);
//     cout << "0";
//     MoveCursor(MapSize + 1,0);
//     cout << "0";
//     MoveCursor(0,MapSize + 1);
//     cout << "0";
//     MoveCursor(MapSize + 1,MapSize + 1);
//     cout << "0";
// }