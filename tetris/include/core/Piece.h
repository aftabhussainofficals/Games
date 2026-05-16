#pragma once
#include "../ui/piecedata.h"
#include "../ui/colors.h"

class Piece {
public:
    int  col;
    int  row;
    int  typeIndex;
    Grid shape;

    Piece();
    void resetPosition();
};
