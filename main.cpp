#include <iostream>
#include <Windows.h>

int main() {
    std::cout << "hello";
    system("mode con: cols=64 lines=32");
    system("pause");
    return 0;
}