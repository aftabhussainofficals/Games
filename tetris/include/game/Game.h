#pragma once
#include "../core/Board.h"
#include "../ui/Menu.h"
#include "../../include/db/ScoreDB.h"

class Game {
public:
    Board board;
    Piece currentPiece;
    Piece nextPiece;

    int  score;
    int  level;
    int  gravityDelay;
    bool gameOver;
    bool paused;
    bool showControls;
    bool isChallenge;

    time_t startTime;

    static const int CHALLENGE_SECS = 300;
    static const int TARGET_SCORE   = 1500;

    Game(bool challenge);
    void run(vector<PlayerRecord>& records, string playerName, string mode);
};
