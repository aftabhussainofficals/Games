#include "../../include/ui/Menu.h"

Menu::Menu(bool modeMenu) {
    selectedOption       = 0;
    isModeSelectionMenu = modeMenu;
}

void Menu::draw() {
    clearScreen();
    moveTop();

    string title, option0, option1;
    if (isModeSelectionMenu) {
        title = "SELECT MODE";
        option0  = "NORMAL";
        option1  = "CHALLENGE";
    } else {
        title = "TETRIS";
        option0  = "PLAY";
        option1  = "EXIT";
    }

    int width = 40;

    printCentered(boldText("\u250c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510"), 20, width);
    cout << "\n";
    printCentered(boldText("\u2502  " + title + string(14 - title.size(), ' ') + "  \u2502"), 20, width);
    cout << "\n";
    printCentered(boldText("\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518"), 20, width);
    cout << "\n\n";

    string options[2] = { option0, option1 };
    for (int i = 0; i < 2; i++) {
        string line;
        if (i == selectedOption)
            line = colorCode(32) + boldText(" > " + options[i] + " < ");
        else
            line = "   " + options[i] + "   ";
        printCentered(line, options[i].size() + 6, width);
        cout << "\n";
    }

    cout << "\n";
    printCentered("W/S to move, ENTER to select", 28, width);
    cout << "\n";
}

int Menu::run() {
    hideCursor();
    draw();
    while (true) {
        char key = readKey();
        if (key == 'w' || key == 's') {
            selectedOption = 1 - selectedOption;
            draw();
        } else if (key == '\r' || key == '\n') {
            showCursor();
            return selectedOption;
        }
    }
}

void showCountdown() {
    int width = 40;
    for (int digit = 3; digit >= 1; digit--) {
        clearScreen();
        moveTop();
        cout << "\n\n\n";

        for (int rowIndex = 0; rowIndex < 5; rowIndex++) {
            const char* row = getCountdownRow(digit, rowIndex);
            string line = colorCode(93) + boldText(row) + resetStr();
            printCentered(line, strlen(row), width);
            cout << "\n";
        }

        cout.flush();
        Sleep(900);
    }
    clearScreen();
}
