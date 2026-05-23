#include "Game.h"

void cls() { system("cls"); }

void drawMenu(int selected, vector<Game*>& allGames) {
    cls();
    cout << "\n";
    cout << "   ==============================\n";
    cout << "  |         GAME  HUB            |\n";
    cout << "   ==============================\n\n";

    for (int i = 0; i < 5; i++) {
        string label;
        if      (i < 3)  label = allGames[i]->getTitle();
        else if (i == 3) label = "Random Game";
        else             label = "Exit";

        if (i == selected)
            cout << "  \033[32m > " << label << " \033[0m\n";
        else
            cout << "     " << label << "\n";
    }

    cout << "\n  W/S to navigate, ENTER to select\n";
}

int main() {
    srand((unsigned)time(nullptr));
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    hideCursor();

    vector<Game*> allGames = {
        new TetrisGame(),
        new UnavailableGame("Snake"),
        new UnavailableGame("Breakout")
    };

    int selected = 0;
    const int TOTAL = 5;

    drawMenu(selected, allGames);

    while (true) {
        int ch = _getch();
        if (ch == 0 || ch == 224) ch = _getch();

        if (ch == 'w' || ch == 'W' || ch == 72) {
            selected = (selected - 1 + TOTAL) % TOTAL;
            drawMenu(selected, allGames);
        } else if (ch == 's' || ch == 'S' || ch == 80) {
            selected = (selected + 1) % TOTAL;
            drawMenu(selected, allGames);
        } else if (ch == '\r') {
            if (selected >= 0 && selected <= 2) {
                allGames[selected]->play();              // polymorphic call
            } else if (selected == 3) {
                // pick randomly from ALL games — play() handles unavailable itself
                int idx = rand() % 3;
                cls();
                cout << "\n  \033[33mRandomly selected: \033[32m"
                     << allGames[idx]->getTitle() << "\033[0m\n\n";
                allGames[idx]->play();                   // polymorphic call
            } else if (selected == 4) {
                break;
            }
            drawMenu(selected, allGames);
        }
    }

    for (Game* g : allGames) delete g;
    cls();
    cout << "\n  Goodbye!\n\n";
    return 0;
}
