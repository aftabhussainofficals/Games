#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// a 2D grid of ints — used for piece shapes and the board
typedef vector<vector<int>> Grid;

void setupConsole();
void moveTop();
void hideCursor();
void showCursor();
void clearScreen();

char   readKey();
string pad16(string s);
void   printCentered(string text, int visibleLen, int width = 40);
