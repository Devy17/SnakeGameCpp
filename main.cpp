#include <iostream>
#include <Windows.h>

#define MapSize 32

using namespace std;

#pragma region 함수 선언
void Init();
void DrawWall();
void Draw();
void MoveCursor(int x, int y);
#pragma endregion

char screen[MapSize][MapSize];

int main() {
    Init();
    DrawWall();
    while(1){
        Draw();
    }
    return 0;
}

void Init() {
    // 창 크기 고정 및 제목 설정
    system("mode con: cols=66 lines=34 | title Snake");

    // 커서 숨김
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void DrawWall() {
    // 상하 벽 생성
    for(int i = 1; i < MapSize; i++) {
        MoveCursor(i,0);
        cout << "--";
        MoveCursor(i, MapSize + 1);
        cout << "--";
    }
    // 좌우 벽 생성
    for(int i = 1; i < MapSize + 1; i++) {
        MoveCursor(0,i);
        cout << "|";
        MoveCursor(MapSize, i);
        cout << " |";
    }
    // 꼭짓점 생성
    MoveCursor(0,0);
    cout << "0-";
    MoveCursor(MapSize,0);
    cout << "-0";
    MoveCursor(0,MapSize + 1);
    cout << "0-";
    MoveCursor(MapSize,MapSize + 1);
    cout << "-0";
}

void Draw() {
    int a;
    a = 0;
}

void MoveCursor(int x, int y) {
    COORD coord;
    coord.X = x * 2;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}