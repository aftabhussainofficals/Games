#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

inline void hideCursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(h, &ci);
    ci.bVisible = false;
    SetConsoleCursorInfo(h, &ci);
}


class Game {
public:
    Game(string t) : title(t) {}
    virtual void play()            = 0;
    virtual bool isAvailable()     const { return false; }
    virtual ~Game() {}
    string getTitle() const { return title; }
private:
    string title;
};


class TetrisGame : public Game {
public:
    TetrisGame() : Game("Tetris") {}

    virtual bool isAvailable() const override {
        
        DWORD attr = GetFileAttributesA("tetris\\tetris.exe");
        return (attr != INVALID_FILE_ATTRIBUTES);
    }

    virtual void play() override {
        if (isAvailable()) {
            system("cd tetris && tetris.exe");
        } else {
            cout << "\n  Tetris executable not found.\n";
            cout << "  Run tetris/build.bat first.\n";
            cout << "\n  Press any key to go back...\n";
            _getch();
        }
    }
};


class UnavailableGame : public Game {
public:
    UnavailableGame(string name) : Game(name) {}

    virtual bool isAvailable() const override { return false; }

    virtual void play() override {
        cout << "\n  \"" << getTitle() << "\" is coming soon!\n";
        cout << "  Press any key to go back...\n";
        _getch();
    }
};
