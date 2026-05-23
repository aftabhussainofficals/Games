#pragma once
#include "../core/Board.h"
#include "../ui/Menu.h"

class BaseGame {
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

    time_t startTime;

    BaseGame() :
        score(0), level(1), gravityDelay(500),
        gameOver(false), paused(false), showControls(false),
        startTime(time(nullptr)) {}

    virtual ~BaseGame() {}

    // Subclasses define their own win/lose conditions
    virtual bool isGameOver()       const { return gameOver; }
    // Subclasses return the time string appropriate for their mode
    virtual string getTimeDisplay() const = 0;
    // Subclasses return true if challenge mode
    virtual bool   isChallenge()    const { return false; }
};
