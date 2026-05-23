#include "../../include/game/Game.h"
#include "../../include/game/GameTime.h"
#include "../../include/game/GameLogic.h"
#include "../../include/game/GameInput.h"
#include "../../include/game/GameDraw.h"

Game::Game(bool challenge) : BaseGame() {
    isChallengeMember = challenge;
    spawnNext(*this);
}

string Game::getTimeDisplay() const {
    return formatTime(elapsedSeconds(startTime));
}

void Game::run(vector<PlayerRecord>& records, string playerName, string mode) {
    clearScreen();
    hideCursor();

    DWORD lastTick = GetTickCount();

    while (!isGameOver()) {
        handleInput(*this);

        DWORD now     = GetTickCount();
        DWORD elapsed = now - lastTick;

        if (elapsed >= (DWORD)gravityDelay) {
            updateGame(*this);
            lastTick = GetTickCount();
        }

        drawGame(*this);
        Sleep(16);
    }

    gameOver = true;
    updatePlayer(records, playerName, score, level, mode);
    showGameOver(*this, records, playerName);
    showCursor();
}
