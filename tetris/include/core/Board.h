#pragma once
#include "Piece.h"

class Board {
public:
    static const int WIDTH  = 10;
    static const int HEIGHT = 20;

    Grid grid;

    Board();

    bool hasCollision(Piece& piece, int newCol, int newRow);
    void lockPiece(Piece& piece);
    int  clearFullLines();
    int  getGhostRow(Piece& piece);
    void drawRow(int row, Piece& piece, int ghostRow);
};
