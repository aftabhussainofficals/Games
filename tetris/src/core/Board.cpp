#include "../../include/core/Board.h"

Board::Board() {
    grid.assign(HEIGHT, vector<int>(WIDTH, 0));
}

bool Board::hasCollision(Piece& piece, int newCol, int newRow) {
    for (int shapeRow = 0; shapeRow < piece.shape.size(); shapeRow++) {
        for (int shapeCol = 0; shapeCol < piece.shape[shapeRow].size(); shapeCol++) {
            if (piece.shape[shapeRow][shapeCol] == 0) continue;

            int boardRow = newRow + shapeRow;
            int boardCol = newCol + shapeCol;

            if (boardRow < 0 || boardRow >= HEIGHT) return true;
            if (boardCol < 0 || boardCol >= WIDTH)  return true;
            if (grid[boardRow][boardCol] != 0)       return true;
        }
    }
    return false;
}

void Board::lockPiece(Piece& piece) {
    for (int shapeRow = 0; shapeRow < piece.shape.size(); shapeRow++) {
        for (int shapeCol = 0; shapeCol < piece.shape[shapeRow].size(); shapeCol++) {
            if (piece.shape[shapeRow][shapeCol] != 0) {
                grid[piece.row + shapeRow][piece.col + shapeCol] = piece.typeIndex + 1;
            }
        }
    }
}

int Board::clearFullLines() {
    int linesCleared = 0;
    for (int row = HEIGHT - 1; row >= 0; row--) {
        bool isFull = true;
        for (int col = 0; col < WIDTH; col++) {
            if (grid[row][col] == 0) { isFull = false; break; }
        }
        if (isFull) {
            grid.erase(grid.begin() + row);
            grid.insert(grid.begin(), vector<int>(WIDTH, 0));
            linesCleared++;
            row++;
        }
    }
    return linesCleared;
}

int Board::getGhostRow(Piece& piece) {
    int ghostRow = piece.row;
    while (!hasCollision(piece, piece.col, ghostRow + 1)) ghostRow++;
    return ghostRow;
}

void Board::drawRow(int row, Piece& piece, int ghostRow) {
    for (int col = 0; col < WIDTH; col++) {
        int shapeRow      = row - piece.row;
        int shapeCol      = col - piece.col;
        int ghostShapeRow = row - ghostRow;

        bool isActivePiece = false;
        if (shapeRow >= 0 && shapeRow < piece.shape.size() &&
            shapeCol >= 0 && shapeCol < piece.shape[shapeRow].size())
            isActivePiece = (piece.shape[shapeRow][shapeCol] != 0);

        bool isGhostPiece = false;
        if (ghostShapeRow >= 0 && ghostShapeRow < piece.shape.size() &&
            shapeCol >= 0 && shapeCol < piece.shape[ghostShapeRow].size())
            isGhostPiece = (piece.shape[ghostShapeRow][shapeCol] != 0);

        if (isActivePiece)
            cout << colorCode(getPieceColor(piece.typeIndex)) << "[]" << resetStr();
        else if (grid[row][col] != 0)
            cout << colorCode(getPieceColor(grid[row][col] - 1)) << "[]" << resetStr();
        else if (isGhostPiece)
            cout << colorCode(getPieceColor(piece.typeIndex)) << "\u2591\u2591" << resetStr();
        else
            cout << "  ";
    }
}
