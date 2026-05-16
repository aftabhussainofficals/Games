#include "../../include/ui/piecedata.h"

static const int PIECE_COLORS[7] = { 33, 36, 35, 32, 34, 31, 93 };

static const vector<Grid> PIECE_SHAPES = {
    {{1,1},{1,1}},        // O
    {{1,1,1,1}},          // I
    {{0,1,0},{1,1,1}},    // T
    {{1,0},{1,0},{1,1}},  // L
    {{0,1},{0,1},{1,1}},  // J
    {{0,1,1},{1,1,0}},    // S
    {{1,1,0},{0,1,1}},    // Z
};

// 7-segment style digits using [] blocks, each digit is 5 rows x 6 chars wide
// segments: top, top-right, bottom-right, bottom, bottom-left, top-left, middle
static const char* COUNTDOWN_DIGITS[4][5] = {
    { nullptr,     nullptr,     nullptr,     nullptr,     nullptr     },  // 0 unused
    { "  []  ",   "  []  ",   "  []  ",   "  []  ",   "  []  "   },  // 1
    { " [][] ",   "   [] ",   " [][] ",   " []   ",   " [][] "   },  // 2
    { " [][] ",   "   [] ",   " [][] ",   "   [] ",   " [][] "   },  // 3
};

int getPieceColor(int typeIndex) { return PIECE_COLORS[typeIndex]; }
Grid getPieceShape(int typeIndex) { return PIECE_SHAPES[typeIndex]; }
const char* getCountdownRow(int digit, int row) { return COUNTDOWN_DIGITS[digit][row]; }
