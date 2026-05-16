#include "../../include/ui/tetris.h"

void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    srand(time(nullptr));
}

void moveTop()     { cout << "\033[H"; }
void hideCursor()  { cout << "\033[?25l"; }
void showCursor()  { cout << "\033[?25h"; }
void clearScreen() { cout << "\033[2J"; }

char readKey() {
    char c = _getch();
    if (c == 0 || c == -32) {
        char c2 = _getch();
        if (c2 == 72) return 'w';
        if (c2 == 80) return 's';
        if (c2 == 75) return 'a';
        if (c2 == 77) return 'd';
    }
    return tolower(c);
}

string pad16(string s) {
    if (s.size() > 16) {
        s = s.substr(0, 16);
    }
    while (s.size() < 16) {
        s += ' ';
    }
    return s;
}

void printCentered(string text, int visibleLen, int width) {
    int leftSpaces = (width - visibleLen) / 2;
    for (int i = 0; i < leftSpaces; i++) {
        cout << ' ';
    }
    cout << text;
}
