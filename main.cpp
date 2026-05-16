#include <iostream>
#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ANSI color codes
#define CYAN    "\033[96m"
#define YELLOW  "\033[93m"
#define GREEN   "\033[92m"
#define RED     "\033[91m"
#define WHITE   "\033[97m"
#define RESET   "\033[0m"

void enableANSI() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printMenu() {
    clearScreen();
    cout << "\n";
    cout << CYAN  "  ╔══════════════════════════════╗\n";
    cout << CYAN  "  ║" YELLOW "        GAMES  ARCADE         " CYAN "║\n";
    cout << CYAN  "  ╠══════════════════════════════╣\n";
    cout << CYAN  "  ║  " GREEN  "1. Tetris                   " CYAN "║\n";
    cout << CYAN  "  ║  " RED    "2. Not Available            " CYAN "║\n";
    cout << CYAN  "  ║  " RED    "3. Not Available            " CYAN "║\n";
    cout << CYAN  "  ║  " WHITE  "0. Exit                     " CYAN "║\n";
    cout << CYAN  "  ╚══════════════════════════════╝" RESET "\n";
    cout << "\n  " YELLOW "Select an option: " RESET;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    enableANSI();
#endif
    int choice;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                clearScreen();
                cout << "\n  Launching Tetris...\n\n";
#ifdef _WIN32
                system("start \"\" \"tetris\\tetris.exe\"");
#else
                system("./tetris/tetris");
#endif
                cout << "\n  Press Enter to return to menu...";
                cin.ignore();
                cin.get();
                break;

            case 2:
            case 3:
                clearScreen();
                cout << "\n  This game is not available yet.\n";
                cout << "\n  Press Enter to return to menu...";
                cin.ignore();
                cin.get();
                break;

            case 0:
                clearScreen();
                cout << "\n  Goodbye!\n\n";
                return 0;

            default:
                cout << "\n  Invalid option. Press Enter to try again...";
                cin.ignore();
                cin.get();
                break;
        }
    }
}
