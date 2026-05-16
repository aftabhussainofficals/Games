#pragma once
#include "tetris.h"

int         getPieceColor(int typeIndex);
Grid        getPieceShape(int typeIndex);
const char* getCountdownRow(int digit, int row);
