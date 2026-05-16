#include "../../include/game/Game.h"
#include "../../include/game/GameTime.h"
#include "../../include/game/GameLogic.h"
#include "../../include/game/GameInput.h"
#include "../../include/game/GameDraw.h"

Game::Game(bool challenge) {
    score        = 0;
    level        = 1;
    gravityDelay = 500;
    gameOver     = false;
    paused       = false;
    showControls = false;
    isChallenge  = challenge;
    startTime    = time(nullptr);
    spawnNext(*this);
}

void Game::run(vector<PlayerRecord>& records, string playerName, string mode) {
    clearScreen();
    hideCursor();

    DWORD lastTick = GetTickCount();

    while (!gameOver) {
        handleInput(*this);

        DWORD now     = GetTickCount();
        DWORD elapsed = now - lastTick;

        if (elapsed >= gravityDelay) {
            updateGame(*this);
            lastTick = GetTickCount();
        }

        drawGame(*this);
        Sleep(16);
    }

    // save score first so leaderboard inside showGameOver is up to date
    updatePlayer(records, playerName, score, level, mode);
    showGameOver(*this, records, playerName);
    showCursor();
}
