#include "../../include/core/Piece.h"

Piece::Piece() {
    typeIndex = rand() % 7;
    shape     = getPieceShape(typeIndex);
    col = 4;
    row = 0;
}

void Piece::resetPosition() {
    col = 4;
    row = 0;
}
