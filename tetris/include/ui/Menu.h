#pragma once
#include "tetris.h"
#include "colors.h"
#include "piecedata.h"

class Menu {
public:
    int  selectedOption;
    bool isModeSelectionMenu;

    Menu(bool modeMenu);

    void draw();
    int  run();
};

void showCountdown();
